#ifndef MYTABLE_H2
#define MYTABLE_H2

#include <QString>
#include <QDateTime>

class gasConcentrationTable
{
public:
    gasConcentrationTable();
    bool setData(QString result);
    //~gasConcentrationTable();
public:
    static QString TableName;
    int PNumber;
    QString GasName;
    QString GasConcentration;
    QDateTime GasTime;
};

class gasView
{
public:
    gasView();
    int ID;
    int PNumber;
    QString GasConcentration;
    QDateTime GasTime;
};

bool isDigitStr2(QString src);
#endif // MYTABLE_H2
