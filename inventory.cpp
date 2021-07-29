#include "inventory.h"

inventory::inventory(QWidget *parent, int countColumn, int countRow):
    QTableWidget(parent),
    cColumn(countColumn),
    cRow(countRow)
{
    setColumnCount(cColumn);
    setRowCount(cRow);

    setObjectName(QString::fromUtf8("inventory"));
    horizontalHeader()->setVisible(false);
    verticalHeader()->setVisible(false);
    horizontalHeader()->setDefaultSectionSize(150);
    verticalHeader()->setDefaultSectionSize(150);

    setDragDropMode(QAbstractItemView::DragDrop);
    setDragDropOverwriteMode(true);
    setDropIndicatorShown(true);
    vInfoTable.fill(itemCellInfo, (cColumn * cRow));
    setEditTriggers(QAbstractItemView::NoEditTriggers);
    setFocusPolicy(Qt::NoFocus);

    setFixedWidth(cColumn * 150 + 2);
    setFixedHeight(cRow * 150 + 2);

    connect(this, &inventory::isRightClickOnCell,
            this, &inventory::rightClickOnCell);
}

inventory::~inventory()
{
    QTableWidget::clear();
    sqlDataBase.clearTableInDataBase();
}

/*
 *
 * Переопределёный обработчик события завершения переноса объекта
 *
*/
void inventory::dropEvent(QDropEvent *event)
{
    QModelIndex index = indexAt(event->pos()); //координаты сброса бом... предмета)
    int newPos = index.row() * cColumn + index.column(); //позиция обьекта в одномерном массиве
    if (event->source() == this && currentRow() >= 0 && currentColumn() >= 0) { // проверка на принадлежность перетаскиваемого объекта текущей таблице
        int oldPos = currentIndex().row() * cColumn + currentIndex().column();
        if (itemAt(event->pos()) == nullptr) { //обработчик переноса обьекта в новую пустую клетку
            setItem(index.row(), index.column(), takeItem(currentRow(), currentColumn()));
            vInfoTable[newPos] = vInfoTable[oldPos];
            vInfoTable[oldPos] = itemCellInfo;
            //перенос данных в БД
            sqlDataBase.insertDataIntoDataBase(QString("inventory"),
                                               vInfoTable[newPos].itemName,
                                               newPos,
                                               vInfoTable[newPos].count);
            sqlDataBase.deleteItemFromDatabase(oldPos); //удаляем данный о прошлом положении
        } else {
            if (vInfoTable[newPos].itemName
                    == vInfoTable[oldPos].itemName) { //обработка совмещения двух одинаковый предметов в таблице
                vInfoTable[newPos].count += vInfoTable[oldPos].count;
                vInfoTable[oldPos] = itemCellInfo;
                itemAt(event->pos())->setText(QString::number(vInfoTable[newPos].count));
                delete item(currentRow(), currentColumn());
                //обновление данных в БД
                sqlDataBase.updateItemOnDataBase(newPos,
                                                vInfoTable[newPos].count);
                sqlDataBase.deleteItemFromDatabase(oldPos);
            }
        }
    } else if (event->source() != this) { //обработка преноса предмета не принадлежащего текущей таблице
        if (!vInfoTable[newPos].count) {  //обработчик переноса обьекта в новую пустую клетку
            vInfoTable[newPos].itemName = event->mimeData()->text();
            setItem(index.row(), index.column(), new QTableWidgetItem(QString::number(++vInfoTable[newPos].count)));
            itemAt(event->pos())->setFont(QFont("Times", 8));
            itemAt(event->pos())->setTextAlignment(Qt::AlignBottom | Qt::AlignRight);
            itemAt(event->pos())->setData(Qt::DecorationRole, qvariant_cast<QPixmap>(event->mimeData()->imageData()));
            sqlDataBase.insertDataIntoDataBase(QString("inventory"),
                                               vInfoTable[newPos].itemName,
                                               newPos,
                                               vInfoTable[newPos].count);
        } else if(vInfoTable[newPos].itemName == event->mimeData()->text()) { //обработчик события, если клетка не пустая
            itemAt(event->pos())->setText(QString::number(++vInfoTable[newPos].count));
            sqlDataBase.updateItemOnDataBase(newPos,
                                            vInfoTable[newPos].count);
        }
        setDragDropMode(QAbstractItemView::DragDrop);
        QTableWidget::dropEvent(event); // передадим контроль за переносом обратно на стандартный метод
    }
//    event->acceptProposedAction();
    clearSelection();
}
/*
 * Метод служащий для обработки входного события переноса в таблицу
 */
void inventory::dragEnterEvent(QDragEnterEvent *event)
{
    /*добавить проверку*/
    setDragDropMode(QAbstractItemView::InternalMove);
    event->acceptProposedAction(); // разрешим сброс предметов в текущей таблице
}

/*
 * Метод обрабатывающийнажатия правой кнопки мыши в клетке
 * */

void inventory::rightClickOnCell(int _row, int _column)
{
    int position = _row * cColumn + _column; //позиция в одномерном массиве
    if (item(_row, _column) != nullptr) { // если клетка не пустая
        item(_row, _column)->setText(QString::number(--vInfoTable[position].count)); // декримент колличества предметов в клетке
        QSound::play(":/audio/sound" + vInfoTable[position].itemName + ".wav"); // простое воспроизведения звука
        sqlDataBase.selectItemFromDataBase(position);
        sqlDataBase.updateItemOnDataBase(position,
                                        vInfoTable[position].count);
        if (vInfoTable[position].count == 0) { // если колличество элементов равно 0, то удаляем предмет из таблицы и базы данных
            vInfoTable[position] = itemCellInfo;
            delete item(_row, _column);
            sqlDataBase.deleteItemFromDatabase(position); //удаляем запись в базе данных
        }
    }
}

/*
 * метод служащий для очистки игровой области
 * */
void inventory::clear()
{
    /* переделать */
    vInfoTable.fill(itemCellInfo, (cColumn * cRow)); // обнуляем информацию о предметах в ячейках
    sqlDataBase.clearTableInDataBase(); // удаляем все данные из бд в талбице инвентаря
    QTableWidget::clear(); //стандартный метод очистки таблици
}

bool inventory::dropMimeData(int row, int column, const QMimeData *data, Qt::DropAction action)
{
    return QTableWidget::dropMimeData(row, column,  data, action);
}

QMimeData *inventory::mimeData(const QList<QTableWidgetItem *> items) const
{
    QMimeData *md = QTableWidget::mimeData(items);
    md->setText("reimplementMime");
    return md;
}


/*
 * Переопределённый метод обработчика нажатия кнопки мыши
 *
 * */
void inventory::mousePressEvent(QMouseEvent *event)
{
    QModelIndex index = indexAt(event->pos()); //координаты нажатия мыши
    if (event->button() == Qt::RightButton) { // если это правая кнопка отправляем сигнал о том что она была нажата и координаты в табилце
        emit isRightClickOnCell(index.row(), index.column());
    } else if (event->button() == Qt::LeftButton) { // если это была левая и ячейка непустая оправляем сигнал в стандартный обработчик этого события для DnD
        if (itemFromIndex(index) != nullptr) {
            QTableWidget::mousePressEvent(event);
        } else {
            event->ignore();
        }
    }
}
