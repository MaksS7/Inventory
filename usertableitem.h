#ifndef USERTABLEITEM_H
#define USERTABLEITEM_H

#include <QTableWidgetItem>
#include <QString>

class userTableItem : public QTableWidget
{
public:
    explicit userTableItem(QWidget *parent = nullptr, QString name = " ");
    QString getNameItem() const {return nameItem;}
private:
    QString nameItem;
    QPixmap image;
protected:
    QMimeData *mimeData(const QList<QTableWidgetItem *> items) const override;
};

#endif // USERTABLEITEM_H
