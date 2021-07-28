#ifndef USERTABLEITEM_H
#define USERTABLEITEM_H

#include <QTableWidgetItem>
#include <QString>

class userTableItem : public QTableWidgetItem
{
public:
    userTableItem(QString name);
private:
    QString nameItem;
    QPixmap image;
protected:

};

#endif // USERTABLEITEM_H
