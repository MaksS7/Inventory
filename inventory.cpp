#include "inventory.h"


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

    connect(this, &inventory::isRightClickOnCell,
            this, &inventory::rightClickOnCell);
}

void inventory::dropEvent(QDropEvent *event)
{
    QModelIndex index = indexAt(event->pos());
    if (event->source() == this && currentRow() >= 0 && currentColumn() >= 0) {
        if (itemAt(event->pos()) == nullptr) {
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
            itemAt(event->pos())->setData(Qt::DecorationRole, qvariant_cast<QPixmap>(event->mimeData()->imageData()));
        } else if(vInfoTable[index.row() * cColumn + index.column()].itemName == event->mimeData()->text()) {
            itemAt(event->pos())->setText(QString::number(++vInfoTable[index.row() * cColumn + index.column()].count));
        }
    }
    clearSelection();
}

void inventory::dragEnterEvent(QDragEnterEvent *event)
{
    /*добавить проверку*/
    event->acceptProposedAction();
}

void inventory::rightClickOnCell(int _row, int _column)
{
    if (item(_row, _column) != nullptr) {
        item(_row, _column)->setText(QString::number(--vInfoTable[_row * cColumn + _column].count));
        if (vInfoTable[_row * cColumn + _column].count == 0) {
            vInfoTable[_row * cColumn + _column] = itemCellInfo;
            takeItem(_row, _column);
        }
        soundDorPlay.play();
    }
}

void inventory::clear()
{
    /* переделать */
    vInfoTable.fill(itemCellInfo, (cColumn * cRow));
    QTableWidget::clear();
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
