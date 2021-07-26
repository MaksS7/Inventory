#include "inventory.h"

inventory::inventory(QWidget *parent):
    QTableWidget(parent)
{
    setAcceptDrops(true);
}

void inventory::dragEnterEvent(QDragEnterEvent *event)
{
    qDebug() << "t1";
//    if ( event->mimeData()->hasFormat("application/x-qt-image") && event->mimeData()->hasFormat("text/plain"))
        event->acceptProposedAction();
}

void inventory::dropEvent(QDropEvent *event)
{
//    textBrowser->setPlainText(event->mimeData()->text());
//    mimeTypeCombo->clear();
//    mimeTypeCombo->addItems(event->mimeData()->formats());
    qDebug()<< this->currentColumn();

    event->acceptProposedAction();
}
