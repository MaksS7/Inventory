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
#include <QModelIndex>
#include "item.h"
#include <QVector>

class inventory : public QTableWidget
{
    Q_OBJECT
public:
    explicit inventory(QWidget *parent = nullptr);
    void dropEvent(QDropEvent *event) override;
    void dragEnterEvent(QDragEnterEvent *event) override;

private:
    struct cellInfo
    {
        int count;
        QString itemName;
    } itemCellInfo = {0, " "};
    QVector<cellInfo> vInfoTable;
    int cColumn;
    int cRow;
};

#endif // INVENTORY_H
