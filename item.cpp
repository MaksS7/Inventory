#include "item.h"
#include <QDebug>

/*
 *
 *
 * данный класс реализую предмет как QWidget
 *
 *
 *
 *
 *
 * */
item::item(QWidget *parent) :
    QWidget(parent),
    nameItem("camera"),
    logo(QPixmap(":/Images/"+ nameItem +".jpg").scaled(125,130))
{
    QVBoxLayout* layout = new QVBoxLayout;
    setObjectName(QString::fromUtf8("appleItem"));
    itemImage = new QLabel();
    itemImage->setPixmap(logo);
    itemImage->setAlignment(Qt::AlignHCenter | Qt::AlignVCenter);
    layout->addWidget(itemImage, 0, Qt::AlignHCenter|Qt::AlignVCenter);
    setLayout(layout);
    userDataBase.insertDataIntoDataBase("item", nameItem);
}

/*
 * Переопределнный метод нажатия кнопки мыши
 * служит для активации DnD только, если нажата левая кнопка мыши
 * */
void item::mousePressEvent( QMouseEvent* event ) {
    if (event->button() == Qt::LeftButton) {
        startPosition = event->pos();
    }
}
/*
 * Переопределнный метод движения мыши
 * служит для активации DnD если нажата LMB и совершено движение мышью
 * */
void item::mouseMoveEvent( QMouseEvent *event ) {
    if (!(event->buttons() & Qt::LeftButton)) {
        return;
    }
    if ((event->pos() - startPosition).manhattanLength()
                    < QApplication::startDragDistance()) {
        return;
    }
    QDrag* drag = new QDrag(this);
    QMimeData* mimeData = new QMimeData;
    mimeData->setText(this->nameItem); //запись имени предмета в mime контейнер
    mimeData->setImageData(logo); //запись изображения
    drag->setMimeData(mimeData); //прикрепление mime контейнера к DnD
    drag->setPixmap(this->logo); //установка изображения на время переноса
    drag->setHotSpot(QPoint(this->logo.size().width() / 2,
                            this->logo.size().height() / 2)); // установка мыши на центр переносимого объекта
    drag->exec(Qt::MoveAction); // старт DnD
}
