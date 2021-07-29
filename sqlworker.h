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
    explicit sqlWorker();
    ~sqlWorker();
    void closeConnection();
    bool insertDataIntoDataBase(QString tableName, QString name, int pos = 0, int count = 0);
    bool deleteItemFromDatabase(int pos);
    QVariantList selectItemFromDataBase(int pos);
    bool updateItemOnDataBase(int pos, int count);
    bool clearTableInDataBase();
    void creatTables();

private:
    bool connectToDataBase();
    QSqlDatabase userDataBase;
    QSqlQuery *query;
    const QString path;


};

#endif // SQLWORKER_H
