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

class item : public QWidget
{
    Q_OBJECT
public:
    explicit item(QWidget *parent = nullptr);

private:
    const QString nameItem;
    const QPixmap logo = QPixmap(":/Images/apple.jpg");
    QLabel *itemImage;
signals:

protected:
    void mousePressEvent(QMouseEvent* event);
    void mouseMoveEvent(QMouseEvent* event);
    QPoint startPosition;
};

#endif // ITEM_H