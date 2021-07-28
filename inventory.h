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
//#include "item.h"
#include <QVector>
#include <QPalette>
#include <QSound>
#include "sqlworker.h"
#include "usertableitem.h"

class inventory : public QTableWidget
{
    Q_OBJECT

public:
    explicit inventory(QWidget *parent = nullptr, int countColumn = 1, int countRow = 1);
     ~inventory() override;
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
//    sqlWorker sqlDataBase;

protected:
    bool dropMimeData(int row, int column, const QMimeData *data, Qt::DropAction action) override;
    QMimeData *mimeData(const QList<QTableWidgetItem *> items) const override;
    void mousePressEvent(QMouseEvent* event) override;
};

#endif // INVENTORY_H
