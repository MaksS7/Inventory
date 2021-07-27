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

    if (event->source() == this) {
        if (itemAt(event->pos()) == 0) {
            setItem(index.row(), index.column(), takeItem(currentRow(), currentColumn()));
            vInfoTable[index.row() * cRow + index.column()] = vInfoTable[currentIndex().row() * cRow + currentIndex().column()];
            vInfoTable[currentIndex().row() * cRow + currentIndex().column()] = itemCellInfo;
        } else {
            if (vInfoTable[index.row() * cRow + index.column()].itemName
                    == vInfoTable[currentIndex().row() * cRow + currentIndex().column()].itemName) {
                vInfoTable[index.row() * cRow + index.column()].count += vInfoTable[currentIndex().row() * cRow + currentIndex().column()].count;
                vInfoTable[currentIndex().row() * cRow + currentIndex().column()] = itemCellInfo;
                itemAt(event->pos())->setText(QString::number(vInfoTable[index.row() * cRow + index.column()].count));
                takeItem(currentRow(), currentColumn());
            }
        }
    } else {
        if (!vInfoTable[index.row() * cRow + index.column()].count) {
            vInfoTable[index.row() * cRow + index.column()].itemName = event->mimeData()->text();
            setItem(index.row(), index.column(), new QTableWidgetItem(QString::number(++vInfoTable[index.row() * cRow + index.column()].count)));
            itemAt(event->pos())->setTextAlignment(Qt::AlignBottom | Qt::AlignRight);
            itemAt(event->pos())->setBackground(QBrush(qvariant_cast<QImage>(event->mimeData()->imageData()).scaled(100,100)));
        } else if(vInfoTable[index.row() * cRow + index.column()].itemName == event->mimeData()->text()) {
            itemAt(event->pos())->setText(QString::number(++vInfoTable[index.row() * cRow + index.column()].count));
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
        item(_row, _column)->setText(QString::number(--vInfoTable[_row * cRow + _column].count));
        if (vInfoTable[_row * cRow + _column].count == 0) {
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
    }

}

void inventory::mouseMoveEvent( QMouseEvent *event ) {
    QTableWidget::mouseMoveEvent(event);
}
