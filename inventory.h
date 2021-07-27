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
#include <QPalette>
#include <QSound>

class inventory : public QTableWidget
{
    Q_OBJECT

public:
    explicit inventory(QWidget *parent = nullptr);
    void dropEvent(QDropEvent *event) override;
    void dragEnterEvent(QDragEnterEvent *event) override;

signals:
    void isRightClickOnCell(int cRow, int cColumn);

public slots:
    void rightClickOnCell(int _row, int _column);
    void clear();

private:
    struct cellInfo
    {
        int count;
        QString itemName;
    } itemCellInfo = {0, " "};

    QVector<cellInfo> vInfoTable;
    int cColumn;
    int cRow;
    QSound soundDorPlay;

protected:
    void mousePressEvent(QMouseEvent* event) override;
};

#endif // INVENTORY_H
