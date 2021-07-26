#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    ui->gameField->setEnabled(false);
}

MainWindow::~MainWindow()
{
    delete ui;
}


void MainWindow::on_btnNewGame_clicked()
{
    ui->gameField->setEnabled(!ui->gameField->isEnabled());
    ui->mainMenu->close();
}


void MainWindow::on_btnMainMenu_clicked()
{
    ui->gameField->setEnabled(!ui->gameField->isEnabled());
    ui->mainMenu->show();
}
