#include "mydbadapter.h"
#include "mytable.h"
#include <QMessageBox>
#include <QDebug>
#include <QSettings>
#include <QFileInfo>
#include <iostream>

using namespace std;

myDBAdapter::myDBAdapter()
{
    initSQL();
}
myDBAdapter::~myDBAdapter(){

}
bool myDBAdapter::initSQL()
{
    QFileInfo fi("temAndHum.ini");
    if(!fi.isFile())
    {
        WriteSettings();
    }
    QSettings settings("temAndHum.ini",QSettings::IniFormat);
    db = QSqlDatabase::addDatabase("QMYSQL");
    db.setHostName(settings.value("MySQL/HostName").toString());     //settings.value("MySQL/HostName").toString()读注册表
    db.setDatabaseName(settings.value("MySQL/DataBaseName").toString());
    db.setUserName(settings.value("MySQL/UserName").toString());
    db.setPassword(settings.value("MySQL/PassWord").toString());

    if(!db.open())
    {
        return false;
    }
    else
    {
        QSqlQuery query(db);
        query.exec("create table testOpen(id int primary key,name varchar(20))");
    }
    return true;
}

void myDBAdapter::insertSerial(QString result)   ///插入数据到数据库中
{
    QSqlQuery query(db);
    if(temandhum.setData(result))
    {
        QString in;
        in = QString("insert into %1 values(NULL,%2,'%3','%4','%5')").arg(temandhum.TableName).arg(QString::number(temandhum.PNumber)).arg(temandhum.Tem).arg(temandhum.Hum).arg(temandhum.Date);
        cout<<"over..."<<in.toStdString()<<endl;
        query.exec(in);
    }
}

void myDBAdapter::clearAll()   //清除数据库
{
    QSqlQuery query(db);
    query.exec(QString("delete from %1").arg(temandhum.TableName));  //delete删除表中的数据
    query.exec(QString("ALTER TABLE %1 AUTO_INCREMENT=1").arg(temandhum.TableName));  //使id从1开始自增
}

bool myDBAdapter::isOpen()
{

    QSqlQuery query(db);
    bool result = query.exec("select * from testOpen");
    return result;
}

bool myDBAdapter::reOpen()  //数据库打开了返回false，数据库没打开但已经初始化了返回true，数据库没打开但也没有初始化返回false
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

void WriteSettings()
{
    QSettings settings("temAndHum.ini",QSettings::IniFormat);
    settings.beginGroup("MySQL");
    settings.setValue("HostName","localhost");  //写进注册表中
    settings.setValue("DataBaseName","temandhum");
    settings.setValue("UserName","root");
    settings.setValue("PassWord","1234");
    settings.endGroup();
}
