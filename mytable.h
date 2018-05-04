#ifndef MYTABLE_H
#define MYTABLE_H

#include <QString>

class temAndHumTable
{
public:
    temAndHumTable();
    bool setData(QString result);
    //~gasConcentrationTable();
public:
    static QString TableName;
    int PNumber;
    QString Tem;
    QString Hum;
    QString Date;
};

bool isDigitStr(QString src);

#endif // MYTABLE_H
