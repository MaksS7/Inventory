#include "mainwindow.h"
#include "ui_mainwindow.h"


MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , items(new userTableItem("camera"))
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    ui->gameField->setEnabled(false);
    ui->tableWidget_2->setItem(0,0,items);
//    if (!sqlDb.connectToDataBase()) {
//        qWarning() << "Can't connection to bd!";
//    }
//    sqlDb.selectItemFromDataBase(1);
}

MainWindow::~MainWindow()
{
    delete ui;
}


void MainWindow::on_btnNewGame_clicked()
{
    ui->gameField->setEnabled(!ui->gameField->isEnabled());
    ui->mainMenu->close();
    ui->tableWidget->clear();
}


void MainWindow::on_btnMainMenu_clicked()
{
    ui->gameField->setEnabled(!ui->gameField->isEnabled());
    ui->mainMenu->show();
}

