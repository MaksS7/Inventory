#include "mainwindow.h"
#include "ui_mainwindow.h"


MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
//    , items(new userTableItem("camera"))
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    ui->gameField->setEnabled(false);
//    ui->tableWidget_2->setItem(0,0,items);
//    inventory *lItem = new inventory;
//    lItem->setDefaultDropAction(Qt::CopyAction);
//    lItem->setItem(0,0, new userTableItem("apple"));
    userItem = new userTableItem(nullptr ,"apple");
    ui->vBoxLayoutItem->addWidget(userItem);
    userInventory = new inventory(nullptr, 3, 3);
    ui->vBoxLayoutInventory->addWidget(userInventory);

}

MainWindow::~MainWindow()
{
    delete ui;
}


void MainWindow::on_btnNewGame_clicked()
{
    ui->gameField->setEnabled(!ui->gameField->isEnabled());
    ui->mainMenu->close();
    userInventory->clear();
}


void MainWindow::on_btnMainMenu_clicked()
{
    ui->gameField->setEnabled(!ui->gameField->isEnabled());
    ui->mainMenu->show();
}

