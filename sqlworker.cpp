#include "sqlworker.h"
#include <QDebug>
#include <QFile>

sqlWorker::sqlWorker():
    path("database.db")
{
    if (!QFile(path).exists()) { //проверка существует ли БД, если нет, то создать новую
        connectToDataBase();
        creatTables();
    } else {
        connectToDataBase();
    }
}

sqlWorker::~sqlWorker()
{
    delete query;
}
/*
 *
 * Метод реализующий подключение к базе данных
 *
 * */
bool sqlWorker::connectToDataBase()
{
    if (QSqlDatabase::contains("localDataBase")) { //если база данных уже существует в списке нет смысла добавлять новую
        userDataBase = QSqlDatabase::database("localDataBase");
    } else { //если базы нет, добавляем базу данных в список
        userDataBase = QSqlDatabase::addDatabase("QSQLITE", "localDataBase");
        userDataBase.setDatabaseName(path);
    }
    if (userDataBase.open()) {
        query = new QSqlQuery(userDataBase);
        return true;
    } else {
        return false;
    }

}

void sqlWorker::closeConnection()
{
    if (userDataBase.isOpen()) {
        userDataBase.close();
        delete query;
    }
}
/*
 *
 * Метод добавления данных в базу данных
 * где tableName имя таблицы в БД, name имя предмета, pos позиция в табилце, count количество
 * */
bool sqlWorker::insertDataIntoDataBase(QString tableName, QString name, int pos, int count)
{
    bool state = true;
    if (tableName == "inventory") { //обработка добавления данных в табилцу инвентаря
        if(!query->exec(QString("INSERT INTO " + tableName + " (position, name, count)"
                                "VALUES (%1, '%2', %3);").arg(pos).arg(name).arg(count))) {
            qWarning() << query->lastError().text();
            state = false;
        }
    } else if (tableName == "item") { //обработка для таблицы предмета

        if (!query->exec(QString("SELECT COUNT(*) FROM ") + tableName)) { //проверка на существование предметов в табилце
            qWarning() << query->lastError().text();
            state = false;
        }
        query->next();

        if(!query->value(0).toInt()) { // если в таблице нет данных
            if(!query->exec(QString("INSERT INTO " + tableName + " (name) VALUES ('%1');").arg(name))) {
                qWarning() << query->lastError().text();
                state = false;
            }
        } else { //если в таблице есть данные выполним вставку, если в таблице нет такого значения
            if(!query->exec(QString("INSERT INTO " + tableName + "(name) SELECT '%1' FROM " + tableName +
                                    " WHERE NOT EXISTS(SELECT * FROM " + tableName + " WHERE name='%1');").arg(name))) {
                qWarning() << query->lastError().text();
                state = false;
            }
        }
    }
    return state;
}

/*
 * Метод удаления значения в табилцы
 */

bool sqlWorker::deleteItemFromDatabase(int pos)
{
    if(!query->exec(QString("DELETE FROM inventory WHERE position=%1").arg(pos))) {
        qWarning() << query->lastError().text();
        return false;
    }
    return true;
}

/*
 * считывание данных из таблицы
 */
QVariantList sqlWorker::selectItemFromDataBase(int pos)
{
    if(!query->exec(QString("SELECT * FROM inventory WHERE position=%1").arg(pos))) {
        qWarning() << query->lastError().text();
    }
    query->first();
    QVariantList variantList;
    variantList << query->value("position").toInt()
                << query->value("name").toString()
                << query->value("count").toInt();

    return variantList;
}

bool sqlWorker::updateItemOnDataBase(int pos, int count)
{
    if(!query->exec(QString("UPDATE inventory SET count =%1 WHERE position=%2").arg(count).arg(pos))) {
        qWarning() << query->lastError().text();
        return false;
    }
    return true;
}

bool sqlWorker::clearTableInDataBase()
{
    if(!query->exec(QString("DELETE FROM inventory"))) {
        qWarning() << query->lastError().text();
        return false;
    }
    return true;
}

void sqlWorker::creatTables()
{
    if(!query->exec(QString("CREATE TABLE `inventory` (`position`	INTEGER UNIQUE, `name`	VARCHAR(255), `count`	INTEGER, PRIMARY KEY(position))"))) {
        qWarning() << query->lastError().text();
    }
    if(!query->exec(QString("CREATE TABLE `item` (`number` INTEGER NOT NULL PRIMARY KEY AUTOINCREMENT, `name`	VARCHAR(255) UNIQUE);"))) {
        qWarning() << query->lastError().text();
    }
}

