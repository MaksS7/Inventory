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
inventory::inventory(QWidget *parent, int countColumn, int countRow):
    QTableWidget(parent),
    cColumn(countColumn),
    cRow(countRow)
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

    setDragDropMode(QAbstractItemView::DragDrop);
    setDragDropOverwriteMode(true);
    setDropIndicatorShown(true);
    vInfoTable.fill(itemCellInfo, (cColumn * cRow));
    setEditTriggers(QAbstractItemView::NoEditTriggers);
    setFocusPolicy(Qt::NoFocus);
//    sqlDataBase.connectToDataBase();

    setFixedWidth(cColumn * 100 + 2);
    setFixedHeight(cRow * 100 + 2);

    connect(this, &inventory::isRightClickOnCell,
            this, &inventory::rightClickOnCell);
}

inventory::~inventory()
{
//    sqlDataBase.clearTableInDataBase();
}

void inventory::dropEvent(QDropEvent *event)
{
    QModelIndex index = indexAt(event->pos());
    if (event->source() == this && currentRow() >= 0 && currentColumn() >= 0) {
        if (itemAt(event->pos()) == nullptr) {
            setItem(index.row(), index.column(), takeItem(currentRow(), currentColumn()));
            vInfoTable[index.row() * cColumn + index.column()] = vInfoTable[currentIndex().row() * cColumn + currentIndex().column()];
            vInfoTable[currentIndex().row() * cColumn + currentIndex().column()] = itemCellInfo;
//            sqlDataBase.insertDataIntoDataBase(index.row() * cColumn + index.column(),
//                                               vInfoTable[index.row() * cColumn + index.column()].itemName,
//                                               vInfoTable[index.row() * cColumn + index.column()].count);
        } else {
            if (vInfoTable[index.row() * cColumn + index.column()].itemName
                    == vInfoTable[currentIndex().row() * cColumn + currentIndex().column()].itemName) {
                vInfoTable[index.row() * cColumn + index.column()].count += vInfoTable[currentIndex().row() * cColumn + currentIndex().column()].count;
                vInfoTable[currentIndex().row() * cColumn + currentIndex().column()] = itemCellInfo;
                itemAt(event->pos())->setText(QString::number(vInfoTable[index.row() * cColumn + index.column()].count));
                takeItem(currentRow(), currentColumn());
//                sqlDataBase.updateItemOnDataBse(index.row() * cColumn + index.column(),
//                                                vInfoTable[index.row() * cColumn + index.column()].count);
            }
        }
//        sqlDataBase.deleteItemFromDatabase(currentIndex().row() * cColumn + currentIndex().column());
    } else if (event->source() != this){
        if (!vInfoTable[index.row() * cColumn + index.column()].count) {
            vInfoTable[index.row() * cColumn + index.column()].itemName = event->mimeData()->text();
            setItem(index.row(), index.column(), new QTableWidgetItem(QString::number(++vInfoTable[index.row() * cColumn + index.column()].count)));
            itemAt(event->pos())->setTextAlignment(Qt::AlignBottom | Qt::AlignRight);
            itemAt(event->pos())->setData(Qt::DecorationRole, qvariant_cast<QPixmap>(event->mimeData()->imageData()));
//            sqlDataBase.insertDataIntoDataBase(index.row() * cColumn + index.column(),
//                                               vInfoTable[index.row() * cColumn + index.column()].itemName,
//                                               vInfoTable[index.row() * cColumn + index.column()].count);
        } else if(vInfoTable[index.row() * cColumn + index.column()].itemName == event->mimeData()->text()) {
            itemAt(event->pos())->setText(QString::number(++vInfoTable[index.row() * cColumn + index.column()].count));
//            sqlDataBase.updateItemOnDataBse(index.row() * cColumn + index.column(),
//                                            vInfoTable[index.row() * cColumn + index.column()].count);
        }
        setDragDropMode(QAbstractItemView::DragDrop);
        QTableWidget::dropEvent(event);
    }
//    event->acceptProposedAction();
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
        QSound::play(":/audio/sound" + vInfoTable[_row * cColumn + _column].itemName + ".wav");
//        sqlDataBase.updateItemOnDataBse(_row * cColumn + _column,
//                                        vInfoTable[_row * cColumn + _column].count);
        if (vInfoTable[_row * cColumn + _column].count == 0) {
            vInfoTable[_row * cColumn + _column] = itemCellInfo;
            takeItem(_row, _column);
//            sqlDataBase.deleteItemFromDatabase(_row * cColumn + _column);
        }
    }
}

void inventory::clear()
{
    /* переделать */
    vInfoTable.fill(itemCellInfo, (cColumn * cRow));
//    sqlDataBase.clearTableInDataBase();
    QTableWidget::clear();
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
