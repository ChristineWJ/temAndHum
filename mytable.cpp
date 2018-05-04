#include "mytable.h"
#include <QStringList>
#include <sstream>
#include <iostream>
#include <cstdio>
#include <QDateTime>
#include <QTimer>

using namespace std;

QString temAndHumTable::TableName = "temandhum";

temAndHumTable::temAndHumTable()
{
    PNumber = -1;
    Tem = QString();
    Hum = QString();
}

bool temAndHumTable::setData(QString result)  //???
{
    QString swap = QString(result);
    QStringList list = swap.split(QRegExp("[,\\s]"));
    //cout<<result.toStdString()<<endl;
//    for(int i = 0; i < list.size(); i++)
//        cout<<list[i].toStdString()<<endl;
//    cout<<endl;
    for(int i = 0;i<list.length();i++)
    {

        if(isDigitStr(list[i])&&i==4){
            this->PNumber=list[i].toInt();
        }
        else if(isDigitStr(list[i])&&i == 7)
        {
            this->Tem = list[i];
        }
        else if(isDigitStr(list[i])&&i==10)
        {
            this->Hum=list[i];
        }
    }
    QDateTime time = QDateTime::currentDateTime();
    QString str = time.toString("yyyy-MM-dd hh:mm:ss");
    this->Date = str;
    if(this->Tem.isEmpty()||this->Hum.isEmpty())
    {
        return false;
    }
    return true;

}

bool isDigitStr(QString src)
{
    QByteArray ba = src.toLatin1();

    const char *s = ba.data();

    while(*s && *s>='0' && *s<='9')
    {
        s++;
    }
    if(*s)
    {
        return false;
    }
    else
    {
        return true;
    }
}
