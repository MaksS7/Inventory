#include "item.h"
#include <QDebug>

item::item(QWidget *parent) :
    QWidget(parent),
    nameItem("camera"),
    logo(QPixmap(":/Images/"+ nameItem +".jpg").scaled(100,100))
{
    QVBoxLayout* layout = new QVBoxLayout;
    itemImage = new QLabel();
    itemImage->setPixmap(logo);
    itemImage->setAlignment(Qt::AlignHCenter | Qt::AlignVCenter);
    layout->addWidget(itemImage, 0, Qt::AlignHCenter|Qt::AlignVCenter);
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
    mimeData->setImageData(logo);
    drag->setMimeData(mimeData);
    drag->setPixmap(this->logo);
    drag->setHotSpot(QPoint(this->logo.size().width() / 2,
                            this->logo.size().height() / 2));
    drag->exec(Qt::MoveAction);
}
