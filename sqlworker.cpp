#include "sqlworker.h"
#include <QDebug>

sqlWorker::sqlWorker():
    path("/home/user/fromGit/Qt_testTask/database.db")
{
}

bool sqlWorker::connectToDataBase()
{
    dataBase = QSqlDatabase::addDatabase("QSQLITE");
    dataBase.setDatabaseName(path);
    if (dataBase.open()) {
        query = new QSqlQuery(dataBase);
        return true;
    } else {
        return false;
    }

}

void sqlWorker::closeConnection()
{
    if (dataBase.isOpen()) {
        dataBase.close();
        delete query;
    }
}

void sqlWorker::insertDataIntoDataBase(int pos, QString name, int count)
{
    if(!query->exec(QString("INSERT INTO inventory (position, name, count)"
                    "VALUES (%1, '%2', %3);").arg(pos).arg(name).arg(count))) {
        qWarning() << query->lastError().text();
    }
}

void sqlWorker::deleteItemFromDatabase(int pos)
{
    if(!query->exec(QString("DELETE FROM inventory WHERE position=%1").arg(pos))) {
        qWarning() << query->lastError().text();
    }
}

void sqlWorker::selectItemFromDataBase(int pos)
{
    if(!query->exec(QString("SELECT * FROM inventory WHERE position=%1").arg(pos))) {
        qWarning() << query->lastError().text();
    }

    while(query->next()) {
        qDebug() << query->value("position").toInt();
        qDebug() << query->value("name").toString();
        qDebug() << query->value("count").toInt();
    }
}

void sqlWorker::updateItemOnDataBse(int pos, int count)
{
    if(!query->exec(QString("UPDATE inventory SET count =%1 WHERE position=%2").arg(count).arg(pos))) {
        qWarning() << query->lastError().text();
    }
}

void sqlWorker::clearTableInDataBase()
{
    if(!query->exec(QString("DELETE FROM inventory"))) {
        qWarning() << query->lastError().text();
    }
}
