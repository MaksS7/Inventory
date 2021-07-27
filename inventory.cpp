#include "inventory.h"


inventory::inventory(QWidget *parent):
    QTableWidget(parent),
    cColumn(3),
    cRow(3)
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

    connect(this, &inventory::isRightClickOnCell,
            this, &inventory::rightClickOnCell);
}

void inventory::dropEvent(QDropEvent *event)
{
    QModelIndex index = indexAt(event->pos());
    if (event->source() == this && currentRow() >= 0 && currentColumn() >= 0) {
        if (itemAt(event->pos()) == 0) {
            setItem(index.row(), index.column(), takeItem(currentRow(), currentColumn()));
            vInfoTable[index.row() * cColumn + index.column()] = vInfoTable[currentIndex().row() * cColumn + currentIndex().column()];
            vInfoTable[currentIndex().row() * cColumn + currentIndex().column()] = itemCellInfo;
        } else {
            if (vInfoTable[index.row() * cColumn + index.column()].itemName
                    == vInfoTable[currentIndex().row() * cColumn + currentIndex().column()].itemName) {
                vInfoTable[index.row() * cColumn + index.column()].count += vInfoTable[currentIndex().row() * cColumn + currentIndex().column()].count;
                vInfoTable[currentIndex().row() * cColumn + currentIndex().column()] = itemCellInfo;
                itemAt(event->pos())->setText(QString::number(vInfoTable[index.row() * cColumn + index.column()].count));
                takeItem(currentRow(), currentColumn());
            }
        }
    } else {
        if (!vInfoTable[index.row() * cColumn + index.column()].count) {
            vInfoTable[index.row() * cColumn + index.column()].itemName = event->mimeData()->text();
            setItem(index.row(), index.column(), new QTableWidgetItem(QString::number(++vInfoTable[index.row() * cColumn + index.column()].count)));
            itemAt(event->pos())->setTextAlignment(Qt::AlignBottom | Qt::AlignRight);
            itemAt(event->pos())->setBackground(QBrush(qvariant_cast<QImage>(event->mimeData()->imageData()).scaled(100,100)));
        } else if(vInfoTable[index.row() * cColumn + index.column()].itemName == event->mimeData()->text()) {
            itemAt(event->pos())->setText(QString::number(++vInfoTable[index.row() * cColumn + index.column()].count));
        }
    }
}

void inventory::dragEnterEvent(QDragEnterEvent *event)
{
    /*добавить проверку*/
    event->acceptProposedAction();
}

void inventory::rightClickOnCell(int _row, int _column)
{
    if (item(_row, _column) != 0) {
        item(_row, _column)->setText(QString::number(--vInfoTable[_row * cColumn + _column].count));
        if (vInfoTable[_row * cColumn + _column].count == 0) {
            takeItem(_row, _column);
        }
    }
}

void inventory::mousePressEvent(QMouseEvent *event)
{
    if (event->button() == Qt::RightButton) {
        QModelIndex index = indexAt(event->pos());
        emit isRightClickOnCell(index.row(), index.column());
    } else if (event->button() == Qt::LeftButton) {
        QTableWidget::mousePressEvent(event);
        startPosition = event->pos();
    }
}

void inventory::mouseMoveEvent( QMouseEvent *event ) {
    QTableWidget::mouseMoveEvent(event);
//    QModelIndex index = indexAt(event->pos());
//    QTableWidgetItem *cit = item(index.row(), index.column());
//    if (cit != 0) {
//        if (!(event->buttons() & Qt::LeftButton)){
//            return;
//        }
//        if ((event->pos() - startPosition).manhattanLength()
//                < QApplication::startDragDistance()) {
//            return;
//        }
//        QDrag* drag = new QDrag(this);

//        drag->setMimeData(mimeData({cit}));
//        drag->setPixmap(cit->background().texture());
//        drag->setHotSpot(QPoint(horizontalHeader()->sectionSize(0) / 2,
//                                verticalHeader()->sectionSize(0) / 2));
//        drag->exec(Qt::MoveAction);
//    } else {
//        event->ignore();
//    }

}
