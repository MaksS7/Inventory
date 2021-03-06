#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include "inventory.h"
#include "item.h"
#include "usertableitem.h"

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private slots:
    void on_btnNewGame_clicked();

    void on_btnMainMenu_clicked();

private:
    inventory *userInventory;
    userTableItem *userItem;
    Ui::MainWindow *ui;


};
#endif // MAINWINDOW_H
