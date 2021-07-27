#include "inventory.h"


inventory::inventory(QWidget *parent):
    QTableWidget(parent),
    cColumn(3),
    cRow(3)
{
    setColumnCount(cColumn);
    setRowCount(cRow);
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
}

void inventory::dropEvent(QDropEvent *event)
{
    QModelIndex index = indexAt(event->pos());
    if (event->source() == this) {
        if (itemAt(event->pos()) == 0) {
//            qDebug() << currentIndex();
//            qDebug() << index;
            setItem(index.row(), index.column(), takeItem(currentRow(), currentColumn()));
            vInfoTable[index.row() * cRow + index.column()] = vInfoTable[currentIndex().row() * cRow + currentIndex().column()];
            vInfoTable[currentIndex().row() * cRow + currentIndex().column()] = itemCellInfo;
//            itemAt(event->pos())->setTextAlignment(Qt::AlignBottom | Qt::AlignRight);
//            itemAt(event->pos())->setBackground(QBrush(QPixmap(":/Images/camera.jpg").scaled(100,100)));
        }
    } else {
        if (!vInfoTable[index.row() * cRow + index.column()].count) {
            vInfoTable[index.row() * cRow + index.column()].itemName = event->mimeData()->text();
            setItem(index.row(), index.column(), new QTableWidgetItem(QString::number(++vInfoTable[index.row() * cRow + index.column()].count)));
            itemAt(event->pos())->setTextAlignment(Qt::AlignBottom | Qt::AlignRight);
            itemAt(event->pos())->setBackground(QBrush(QPixmap(":/Images/camera.jpg").scaled(100,100)));
        } else if(vInfoTable[index.row() * cRow + index.column()].itemName == event->mimeData()->text()) {
            itemAt(event->pos())->setText(QString::number(++vInfoTable[index.row() * cRow + index.column()].count));
        }
    }
//    qDebug() << indexAt(event->pos());
}

void inventory::dragEnterEvent(QDragEnterEvent *event)
{
    event->acceptProposedAction();
}


