#ifndef ITEM_H
#define ITEM_H

#include <QWidget>
#include <QString>
#include <QPixmap>
#include <QLabel>
#include <QVBoxLayout>
#include <QMouseEvent>
#include <QDrag>
#include <QMimeData>
#include <QApplication>
#include "sqlworker.h"

class item : public QWidget
{
    Q_OBJECT
public:
    explicit item(QWidget *parent = nullptr);
    /*add "get name and logo*/
private:
    const QString nameItem;
    const QPixmap logo;
    QLabel *itemImage;
    sqlWorker userDataBase;

protected:
    void mousePressEvent(QMouseEvent* event);
    void mouseMoveEvent(QMouseEvent* event);
    QPoint startPosition;
};

#endif // ITEM_H
