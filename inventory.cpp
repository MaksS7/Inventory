#include "inventory.h"

/*
 * *
 * *
 * *
 * **
 * *
 * *
 * *
 * *
 * * сделать один класс просто с возможность выбора клеток
*
*
*
**
*
*
*
*/
inventory::inventory(QWidget *parent):
    QTableWidget(parent),
    cColumn(3),
    cRow(3),
    soundDorPlay(":/audio/soundApple.wav")
{
    setColumnCount(cColumn);
    setRowCount(cRow);
    /*check it*/
    setObjectName(QString::fromUtf8("tableWidget"));
    setGeometry(QRect(0, 60, 302, 302));
    horizontalHeader()->setVisible(false);
    verticalHeader()->setVisible(false);
    horizontalHeader()->setDefaultSectionSize(100);
    verticalHeader()->setDefaultSectionSize(100);

    setDragDropMode(QAbstractItemView::InternalMove);
    setDragDropOverwriteMode(true);
    setDropIndicatorShown(true);
    vInfoTable.fill(itemCellInfo, (cColumn * cRow));
    setEditTriggers(QAbstractItemView::NoEditTriggers);
    setFocusPolicy(Qt::NoFocus);
    sqlDataBase.connectToDataBase();

    connect(this, &inventory::isRightClickOnCell,
            this, &inventory::rightClickOnCell);
}

inventory::~inventory()
{
    sqlDataBase.clearTableInDataBase();
}

void inventory::dropEvent(QDropEvent *event)
{
    QModelIndex index = indexAt(event->pos());
    if (event->source() == this && currentRow() >= 0 && currentColumn() >= 0) {
        if (itemAt(event->pos()) == nullptr) {
            setItem(index.row(), index.column(), takeItem(currentRow(), currentColumn()));
            vInfoTable[index.row() * cColumn + index.column()] = vInfoTable[currentIndex().row() * cColumn + currentIndex().column()];
            vInfoTable[currentIndex().row() * cColumn + currentIndex().column()] = itemCellInfo;
            sqlDataBase.insertDataIntoDataBase(index.row() * cColumn + index.column(),
                                               vInfoTable[index.row() * cColumn + index.column()].itemName,
                                               vInfoTable[index.row() * cColumn + index.column()].count);
        } else {
            if (vInfoTable[index.row() * cColumn + index.column()].itemName
                    == vInfoTable[currentIndex().row() * cColumn + currentIndex().column()].itemName) {
                vInfoTable[index.row() * cColumn + index.column()].count += vInfoTable[currentIndex().row() * cColumn + currentIndex().column()].count;
                vInfoTable[currentIndex().row() * cColumn + currentIndex().column()] = itemCellInfo;
                itemAt(event->pos())->setText(QString::number(vInfoTable[index.row() * cColumn + index.column()].count));
                takeItem(currentRow(), currentColumn());
                sqlDataBase.updateItemOnDataBse(index.row() * cColumn + index.column(),
                                                vInfoTable[index.row() * cColumn + index.column()].count);
            }
        }
        sqlDataBase.deleteItemFromDatabase(currentIndex().row() * cColumn + currentIndex().column());
    } else if (event->source() != this){
        if (!vInfoTable[index.row() * cColumn + index.column()].count) {
            vInfoTable[index.row() * cColumn + index.column()].itemName = event->mimeData()->text();
            setItem(index.row(), index.column(), new QTableWidgetItem(QString::number(++vInfoTable[index.row() * cColumn + index.column()].count)));
            itemAt(event->pos())->setTextAlignment(Qt::AlignBottom | Qt::AlignRight);
            itemAt(event->pos())->setData(Qt::DecorationRole, qvariant_cast<QPixmap>(event->mimeData()->imageData()));
            sqlDataBase.insertDataIntoDataBase(index.row() * cColumn + index.column(),
                                               vInfoTable[index.row() * cColumn + index.column()].itemName,
                                               vInfoTable[index.row() * cColumn + index.column()].count);
        } else if(vInfoTable[index.row() * cColumn + index.column()].itemName == event->mimeData()->text()) {
            itemAt(event->pos())->setText(QString::number(++vInfoTable[index.row() * cColumn + index.column()].count));
            sqlDataBase.updateItemOnDataBse(index.row() * cColumn + index.column(),
                                            vInfoTable[index.row() * cColumn + index.column()].count);
        }
        /*переделать*/
        if (event->source()->objectName() == QString("tableWidget_2")){
            setDragDropMode(QAbstractItemView::DragDrop);
            QTableWidget::dropEvent(event);
        }
    }
    event->acceptProposedAction();
    clearSelection();
}

void inventory::dragEnterEvent(QDragEnterEvent *event)
{
    /*добавить проверку*/
    setDragDropMode(QAbstractItemView::InternalMove);
    event->acceptProposedAction();
}

void inventory::rightClickOnCell(int _row, int _column)
{
    if (item(_row, _column) != nullptr) {
        item(_row, _column)->setText(QString::number(--vInfoTable[_row * cColumn + _column].count));
        sqlDataBase.updateItemOnDataBse(_row * cColumn + _column,
                                        vInfoTable[_row * cColumn + _column].count);
        if (vInfoTable[_row * cColumn + _column].count == 0) {
            vInfoTable[_row * cColumn + _column] = itemCellInfo;
            takeItem(_row, _column);
            sqlDataBase.deleteItemFromDatabase(_row * cColumn + _column);
        }
        soundDorPlay.play();
    }
}

void inventory::clear()
{
    /* переделать */
    vInfoTable.fill(itemCellInfo, (cColumn * cRow));
    sqlDataBase.clearTableInDataBase();
    QTableWidget::clear();
}

bool inventory::dropMimeData(int row, int column, const QMimeData *data, Qt::DropAction action)
{
    qDebug() << "test";
    return QTableWidget::dropMimeData(row, column,  data, action);
}

QMimeData *inventory::mimeData(const QList<QTableWidgetItem *> items) const
{
    qDebug() <<"test1";
    return QTableWidget::mimeData(items);
}

QList<QTableWidgetItem *> inventory::items(const QMimeData *data) const
{
    qDebug()<<"test2";
    return QTableWidget::items(data);
}


void inventory::mousePressEvent(QMouseEvent *event)
{
    QModelIndex index = indexAt(event->pos());
    if (event->button() == Qt::RightButton) {
        emit isRightClickOnCell(index.row(), index.column());
    } else if (event->button() == Qt::LeftButton) {
        if (itemFromIndex(index) != nullptr) {
            QTableWidget::mousePressEvent(event);
        } else {
            event->ignore();
        }
    }
}
