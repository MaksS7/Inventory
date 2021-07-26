#include "inventory.h"

inventory::inventory(QWidget *parent):
    QTableWidget(parent),
    cColumn(3),
    cRow(3)
{
//    setColumnCount(columnCount);
//    setRowCount(rowCount);
    setObjectName(QString::fromUtf8("tableWidget"));
    setGeometry(QRect(0, 60, 302, 302));
    horizontalHeader()->setVisible(false);
    verticalHeader()->setVisible(false);
    horizontalHeader()->setDefaultSectionSize(100);
    verticalHeader()->setDefaultSectionSize(100);
    setDragDropMode(QAbstractItemView::DragDrop);
    setDragDropOverwriteMode(true);
    setDropIndicatorShown(true);

}

void inventory::dropEvent(QDropEvent *event)
{
    // проверяем что источник - родная таблица
    qDebug() << itemAt(10, 10);
//    if (event->source()!=this) {
//        // неродной источник обработаем обработчиком по умолчанию
//        QTableWidget::dropEvent(event);
//    }

//    // определяем цель вставки
//    int targetRow;
//    QTableWidgetItem *targetItem=itemAt(event->pos());
//    if (targetItem!=0) {
//        targetRow=targetItem->row();
//    } else {
//        targetRow = cRow;
//    }
//    qDebug() << targetRow;
//    // запоминаем номера строк
//    QTableWidgetItem *item;
//    QList<int> selRows;
//    foreach (item, selectedItems()) {
//        if (!selRows.contains(item->row())) {
//            // запоминаем номер строки
//            selRows.append(item->row());
//        }
//    }
//    if (selRows.isEmpty()) {
//        event->accept();  // не будем игнорить сообщение, скажем что обработали и передадим дальше
//        return;
//    }

}
