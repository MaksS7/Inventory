#ifndef INVENTORY_H
#define INVENTORY_H

#include <QTableWidget>
#include <QMouseEvent>
#include <QDrag>
#include <QMimeData>
#include <QApplication>
#include <QDebug>
#include <QHeaderView>
#include <QTableWidgetItem>
#include <QIcon>
#include "item.h"

class inventory : public QTableWidget
{
    Q_OBJECT
public:
    explicit inventory(QWidget *parent = nullptr);

    void dropEvent(QDropEvent *event) override;
private:
    int cColumn;
    int cRow;
};

#endif // INVENTORY_H
