#include "usertableitem.h"

userTableItem::userTableItem(QString name) :
    nameItem(name),
    image(QPixmap(":/Images/"+ name +".jpg").scaled(100,100))
{
    setData(Qt::DecorationRole, image);
}
