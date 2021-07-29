#include "usertableitem.h"
#include <QHeaderView>
#include <QDebug>
#include <QMimeData>
#include <QByteArray>
#include <QDataStream>

userTableItem::userTableItem(QWidget *parent, QString name) :
    QTableWidget(parent),
    nameItem(name),
    image(QPixmap(":/Images/"+ name +".jpg").scaled(125,130))
{
    setObjectName(QString(nameItem));
    setColumnCount(1);
    setRowCount(1);
    setItem(0,0, new QTableWidgetItem);
    item(0,0)->setData(Qt::DecorationRole, image);
    setGeometry(QRect(0, 60, 302, 302));
    horizontalHeader()->setVisible(false);
    verticalHeader()->setVisible(false);
    horizontalHeader()->setDefaultSectionSize(150);
    verticalHeader()->setDefaultSectionSize(150);
    sqlDataBase.insertDataIntoDataBase("item", nameItem);

    setDragDropMode(QAbstractItemView::DragDrop);
    setDragDropOverwriteMode(true);
    setDropIndicatorShown(true);
    setEditTriggers(QAbstractItemView::NoEditTriggers);
    setFocusPolicy(Qt::NoFocus);

    setFixedWidth(152);
    setFixedHeight(152);

}
/*
 * Переропределённый метод позволяющий добавить дополнительную информацию в переносимый объект
*/
QMimeData *userTableItem::mimeData(const QList<QTableWidgetItem *> items) const
{
    QMimeData *md = QTableWidget::mimeData(items); //захватываем данный объекта
    md->setText(nameItem); //добавляем к ним имя предмета
    return md;
}
