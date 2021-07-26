#include "item.h"

item::item(QWidget *parent) : QWidget(parent), nameItem("Apple")
{
    QVBoxLayout* layout = new QVBoxLayout;
    itemImage = new QLabel();
    itemImage->setPixmap(logo.scaled(100,100));
    layout->addWidget(itemImage, 0, Qt::AlignCenter);
    itemImage->setAlignment(Qt::AlignHCenter | Qt::AlignVCenter);
    setLayout(layout);
}

void item::mousePressEvent( QMouseEvent* event ) {
    if (event->button() == Qt::LeftButton) {
        startPosition = event->pos();
    }
}

void item::mouseMoveEvent( QMouseEvent *event ) {
    if (!(event->buttons() & Qt::LeftButton)){
        return;
    }
    if ((event->pos() - startPosition).manhattanLength()
                    < QApplication::startDragDistance()) {
        return;
    }
    QDrag* drag = new QDrag(this);
    QMimeData* mimeData = new QMimeData;
    mimeData->setText(this->nameItem);
    mimeData->setParent(this);
    drag->setMimeData(mimeData);
    drag->setPixmap(this->logo.scaled(100,100));
    drag->setHotSpot(QPoint(this->logo.size().width() / 2,
                            this->logo.size().height() / 2));
    drag->exec(Qt::MoveAction);
}
