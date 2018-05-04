#ifndef MYDBADAPTER_H2
#define MYDBADAPTER_H2

#include <QSqlDatabase>
#include <QSqlQuery>
#include <mytable2.h>
#include <QList>
#include <QDebug>

class myDBAdapter2
{
public:
    myDBAdapter2();
    ~myDBAdapter2();
    void insertSerial(QString result);
    void selectAll(QDate date);
    QList<gasView> selectCH4(QDate date);

    QVector<int> selectPNumber();
    QList<gasView> selectGas(QDate date,int s);
    QList<gasView> selectGas(QDate date,QString gasTable);
    void clearAll();
    bool isOpen();
    bool reOpen();

private:
    QSqlDatabase db;
    gasConcentrationTable gas;
    bool initSQL();
};
void WriteSettings2();
#endif // MYDBADAPTER_H2
