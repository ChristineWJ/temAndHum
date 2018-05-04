#ifndef MYDBADAPTER_H
#define MYDBADAPTER_H

#include <QSqlDatabase>
#include <QSqlQuery>
#include <mytable.h>

class myDBAdapter
{
public:
    myDBAdapter();
    ~myDBAdapter();
    void insertSerial(QString result);
    void clearAll();
    bool isOpen();
    bool reOpen();

private:
    QSqlDatabase db;
    temAndHumTable temandhum;
    bool initSQL();
};
void WriteSettings();
#endif // MYDBADAPTER_H
