#include "mainwindow.h"
#include "ui_mainwindow.h"


MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    ui->gameField->setEnabled(false);
    userItem = new userTableItem(nullptr ,"apple");
    ui->vBoxLayoutItem->addWidget(userItem);
    userInventory = new inventory(nullptr, 3, 3);
    ui->vBoxLayoutInventory->addWidget(userInventory);
}

MainWindow::~MainWindow()
{
    delete ui;
}

/*
 * Обработка нажатия клавиши New game
 */
void MainWindow::on_btnNewGame_clicked()
{
    ui->gameField->setEnabled(!ui->gameField->isEnabled());
    ui->mainMenu->close();
    userInventory->clear();
}

/*
 * Обработка нажатия клавиши Main menu
 */
void MainWindow::on_btnMainMenu_clicked()
{
    ui->gameField->setEnabled(!ui->gameField->isEnabled());
    ui->mainMenu->show();
}

