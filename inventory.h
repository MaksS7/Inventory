#ifndef INVENTORY_H
#define INVENTORY_H

#include <QTableWidget>
#include <QMouseEvent>
#include <QDrag>
#include <QMimeData>
#include <QApplication>
#include <QDebug>

class inventory : public QTableWidget
{
    Q_OBJECT
public:
    explicit inventory(QWidget *parent = nullptr);
    void dragEnterEvent(QDragEnterEvent *event);
    void dropEvent(QDropEvent *event);
};

#endif // INVENTORY_H