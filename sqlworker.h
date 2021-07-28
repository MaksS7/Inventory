#ifndef SQLWORKER_H
#define SQLWORKER_H
#include <QSqlDatabase>
#include <QSqlQuery>
#include <QSqlError>
#include <QSqlRecord>
#include <QVariantList>

class sqlWorker
{
public:
    sqlWorker();
    bool connectToDataBase();
    void closeConnection();
    void insertDataIntoDataBase(int pos, QString name, int count);
    void deleteItemFromDatabase(int pos);
    void selectItemFromDataBase(int pos);
    void updateItemOnDataBse(int pos, int count);
    void clearTableInDataBase();

    QSqlDatabase dataBase;
    QSqlQuery *query;
    const QString path;

};

#endif // SQLWORKER_H
