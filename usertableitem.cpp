#include "usertableitem.h"
#include <QHeaderView>
#include <QDebug>
#include <QMimeData>
#include <QByteArray>
#include <QDataStream>

userTableItem::userTableItem(QWidget *parent, QString name) :
    QTableWidget(parent),
    nameItem(name),
    image(QPixmap(":/Images/"+ name +".jpg").scaled(100,100))
{
    setColumnCount(1);
    setRowCount(1);
    setItem(0,0, new QTableWidgetItem);
    item(0,0)->setData(Qt::DecorationRole, image);

    setObjectName(QString::fromUtf8("tableWidget"));
    setGeometry(QRect(0, 60, 302, 302));
    horizontalHeader()->setVisible(false);
    verticalHeader()->setVisible(false);
    horizontalHeader()->setDefaultSectionSize(100);
    verticalHeader()->setDefaultSectionSize(100);

    setDragDropMode(QAbstractItemView::DragDrop);
    setDragDropOverwriteMode(true);
    setDropIndicatorShown(true);
    setEditTriggers(QAbstractItemView::NoEditTriggers);
    setFocusPolicy(Qt::NoFocus);

    setFixedWidth(102);
    setFixedHeight(102);
}

QMimeData *userTableItem::mimeData(const QList<QTableWidgetItem *> items) const
{
    QMimeData *md = QTableWidget::mimeData(items);
    md->setText(nameItem);
    return md;
}
