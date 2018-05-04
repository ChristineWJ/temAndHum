#include "mytable2.h"
#include <QStringList>
#include <sstream>

QString gasConcentrationTable::TableName = "t_gasConcentration";

gasConcentrationTable::gasConcentrationTable()
{
    PNumber = -1;
    GasConcentration = QString();
    GasName = QString();
    GasTime = QDateTime::currentDateTime();
}

bool gasConcentrationTable::setData(QString result)
{
    QString swap = QString(result);
    QStringList list = swap.split(QRegExp("[,. ]"));
    for(int i=0; i<list.length(); i++)
    {
        if(isDigitStr2(list[i])&&i==4)
        {
            this->PNumber=list[i].toInt();
        }
        else if(i==7)
        {
            this->GasName=list[i];
        }
        else if(isDigitStr2(list[i])&&i==9)
        {
            this->GasConcentration=list[i];
        }
    }

    if(this->GasConcentration.isEmpty()||this->PNumber==-1||this->GasName.isEmpty())
    {
        return false;
    }
    return true;
}

gasView::gasView()
{
    this->ID = -1;
    this->PNumber = -1;
    this->GasConcentration = QString();
    this->GasTime = QDateTime::currentDateTime();
}

bool isDigitStr2(QString src)
{
    QByteArray ba = src.toLatin1();//QString 转换为 char*
    const char *s = ba.data();

    while(*s && *s>='0' && *s<='9')
    {
        s++;
    }

    if (*s)
    { //不是纯数字
        return false;
    }
    else
    { //纯数字
        return true;
    }
}
