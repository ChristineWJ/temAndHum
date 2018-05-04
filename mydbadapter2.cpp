#include "mydbadapter2.h"
#include "mytable2.h"
#include <QMessageBox>
#include <QDebug>
#include <QSettings>
#include <QFileInfo>
myDBAdapter2::myDBAdapter2()
{
    initSQL();
}

myDBAdapter2::~myDBAdapter2()
{
    db.close();
}

bool myDBAdapter2::initSQL()
{
    QFileInfo fi("cow.ini");
    if(!fi.isFile())
    {
        WriteSettings2();
    }
    QSettings settings("cow.ini", QSettings::IniFormat);
    db = QSqlDatabase::addDatabase("QMYSQL");
    db.setHostName(settings.value("MySQL/HostName").toString());
    db.setDatabaseName(settings.value("MySQL/DataBaseName").toString());
    db.setUserName(settings.value("MySQL/UserName").toString());
    db.setPassword(settings.value("MySQL/PassWord").toString());

    if (!db.open())
    {
        //qDebug() << "Failed to connect to root mysql admin";
        return false;
    }
    else
    {
        //qDebug() << "open";
        QSqlQuery query(db);
        query.exec("create table testOpen(id int primary key, "
                   "name varchar(20))");
    }
    return true;
}

void myDBAdapter2::insertSerial(QString result)
{
    QSqlQuery query(db);
    if(gas.setData(result))
    {
        QString in;
        in = QString("insert into %1 values(NULL,%2,'%3','%4')").arg(gas.TableName).arg(QString::number(gas.PNumber)).arg(gas.GasName).arg(gas.GasConcentration);
        query.exec(in);
    }
}

void myDBAdapter2::clearAll()
{
    QSqlQuery query(db);
    query.exec(QString("delete from %1").arg(gas.TableName));
    query.exec(QString("ALTER TABLE %1 AUTO_INCREMENT=1;").arg(gas.TableName));
}


bool myDBAdapter2::isOpen()
{
    QSqlQuery query(db);
    bool result = query.exec("select * from testOpen");
    return result;
}

bool myDBAdapter2::reOpen()
{
    if(!isOpen())
    {
       if(initSQL())
       {
           return true;
       }
    }
    return false;
}

void myDBAdapter2::selectAll(QDate date)
{
    QSqlQuery query(db);
    QString str = QString("select * from t_gasconcentration where to_days(DATE) = to_days('%1');").arg(date.toString("yyyy-MM-dd"));
    qDebug()<<str<<endl;
    if(query.exec(str))
    {
        while(query.next())
        {
            qDebug()<<query.at() << "节点号 "<<query.value(1).toInt() << " 气体名称 "<<query.value(2).toString() << " 浓度 " <<query.value(3).toString()
                   <<"日期 "<<query.value(4).toDateTime().toString();
        }
    }

    query.exec("select PNUMBER from t_gasconcentration group by PNUMBER;");
    while(query.next())
    {
        qDebug()<<query.value(0).toInt()<<endl;
    }

}

QList<gasView> myDBAdapter2::selectCH4(QDate date)
{
    QSqlQuery query(db);
    QList<gasView> list;
    gasView gv;
    QString str = QString("select * from gas_ch4 where to_days(DATE) = to_days('%1');").arg(date.toString("yyyy-MM-dd"));
    if(query.exec(str))
    {
        while(query.next())
        {
            gv.PNumber = query.value(1).toInt();
            gv.GasConcentration = query.value(2).toString();
            gv.GasTime = query.value(3).toDateTime();
            list.append(gv);
        }
    }

    return list;
}

QList<gasView> myDBAdapter2::selectGas(QDate date, int s)
{
    QSqlQuery query(db);
    QList<gasView> list;
    gasView gv;
    QString str;
    switch(s)
    {
    case 1:
        str = QString("select * from gas_CH4 where to_days(DATE) = to_days('%1');").arg(date.toString("yyyy-MM-dd"));
        break;
    case 2:
        str = QString("select * from gas_NH3 where to_days(DATE) = to_days('%1');").arg(date.toString("yyyy-MM-dd"));
        break;
    case 3:
        str = QString("select * from gas_H2S where to_days(DATE) = to_days('%1');").arg(date.toString("yyyy-MM-dd"));
        break;
    default:
        break;
    }

    if(query.exec(str))
    {
        while(query.next())
        {
            gv.PNumber = query.value(1).toInt();
            gv.GasConcentration = query.value(2).toString();
            gv.GasTime = query.value(3).toDateTime();
            list.append(gv);
        }
    }

    return list;
}

QList<gasView> myDBAdapter2::selectGas(QDate date, QString gasTable)
{
    QSqlQuery query(db);
    QList<gasView> list;
    gasView gv;
    QString str = QString("select * from %1 where to_days(DATE) = to_days('%2');").arg(gasTable).arg(date.toString("yyyy-MM-dd"));
    if(query.exec(str))
    {
        while(query.next())
        {
            gv.PNumber = query.value(1).toInt();
            gv.GasConcentration = query.value(2).toString();
            gv.GasTime = query.value(3).toDateTime();
            list.append(gv);
        }
    }

    return list;
}

QVector<int> myDBAdapter2::selectPNumber()
{
    QVector<int> num;
    QSqlQuery query(db);
    query.exec("select PNUMBER from t_gasconcentration group by PNUMBER;");
    while(query.next())
    {
       int n = query.value(0).toInt();
       num.append(n);
    }

    return num;
}

void WriteSettings2()
{
    //QSettings settings("Software Inc", "Spreadsheet"); // windows在注册表中建立建 Software Inc -> Spreadsheet
    QSettings settings("cow.ini", QSettings::IniFormat); // 当前目录的INI文件
    settings.beginGroup("MySQL");
    settings.setValue("HostName","localhost");
    settings.setValue("DataBaseName","cow");
    settings.setValue("UserName","root");
    settings.setValue("PassWord","");
    settings.endGroup();
}
