#include "inventory.h"

inventory::inventory(QWidget *parent):
    QTableWidget(parent)
{
    setDragDropMode(QAbstractItemView::InternalMove);
    setDragEnabled(true);
    setAcceptDrops(true);
    setDropIndicatorShown(true);
    setColumnCount(3);
    setRowCount(3);
}

void inventory::dragEnterEvent(QDragEnterEvent *event)
{
//    qDebug() << "Enter:";
//    qDebug() << event->pos();
    if (event->source() == this) {
        event->setDropAction(Qt::MoveAction);
        event->accept();
    } else {
        event->acceptProposedAction();
    }
}

void inventory::dragMoveEvent(QDragMoveEvent *event)
{
//    qDebug() << "move:";
//    qDebug() << event->pos();
    if (event->source() == this) {
        event->setDropAction(Qt::MoveAction);
        event->accept();
    } else {
        event->acceptProposedAction();
    }
}

void inventory::dropEvent(QDropEvent *event)
{
    QTableWidgetItem* test = itemAt(event->pos());
    if  (test != 0)
    {
        qDebug() << event->pos();
        if ( event->source() == this ) // same table, move entry
        {
            event->setDropAction( Qt::MoveAction );
            event->accept();
        }
        else // different table, add entry
        {
            printf("Different table\n");
            event->acceptProposedAction();
        }

            QTableWidgetItem *source = itemAt(event->pos());
            qDebug() << source->column();
            qDebug() << source->row();
            source->setText(itemAt(event->pos())->text());
    }
//    qDebug() << this->itemAt(10,10)->column();
//    QTableWidgetItem *targetItem=itemAt(event->pos());
//    qDebug()<<targetItem->column();
//    qDebug()<<targetItem->row();

    event->acceptProposedAction();
}
