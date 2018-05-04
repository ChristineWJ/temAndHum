#include "showplot.h"
#include "mainwindow.h"
#include "mydbadapter.h"
#include "ui_mainwindow.h"
#include <QSerialPort>
#include <QSerialPortInfo>
#include <QList>
#include <QDebug>
#include <QLabel>
#include <QDateTime>
#include <QTimer>
#include <QMessageBox>
#include <iostream>
#include <QApplication>


using namespace std;
MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    result = "";
    ifInsert = false;
    initSerialPort();
    labelTime = new QLabel(this);
    labelSql = new QLabel(this);
    labelSerial = new QLabel(this);
    serial = new CSerialPort();

    ui->btnOpenCOM->setCheckable(true);
    ui->btnInsertData->setCheckable(true);
    ui->comboBoxPort->setCurrentIndex(1);
    ui->textEdit->setReadOnly(true);
    ui->statusBar->addPermanentWidget(labelTime);
    ui->statusBar->addWidget(labelSql);
    ui->statusBar->addWidget(labelSerial);
    dateTime  = new QTimer();
    connect(dateTime,SIGNAL(timeout()),this,SLOT(timeUpdate()));  //???
    connect(dateTime,SIGNAL(timeout()),this,SLOT(reOpenSql()));   //???
    dateTime->start(1000);
}

MainWindow::~MainWindow()
{
    serial->close();
    delete serial;
    delete ui;
}


//串口初始化函数，将串口号加入到列表中。
bool MainWindow::initSerialPort()
{
    flag = true;
    QList<QSerialPortInfo> infos = QSerialPortInfo::availablePorts();   //？？？
    if(infos.isEmpty())
    {
        ui->comboBoxPort->addItem("无效");
        ui->btnOpenCOM->setEnabled(false);
        return false;
    }
    foreach(QSerialPortInfo info,infos){
        ui->comboBoxPort->addItem(info.portName());
    }
    flag = false;   //flag作用？？？
    return true;
}

void MainWindow::comBoxEnabled(bool x)
{
    ui->comboBoxBuad->setEnabled(x);
    ui->comboBoxData->setEnabled(x);
    ui->comboBoxParity->setEnabled(x);
    ui->comboBoxPort->setEnabled(x);
    ui->comboBoxStop->setEnabled(x);
}

//以下为Qt控件的槽函数。
void MainWindow::on_action_triggered()
{
    ui->comboBoxPort->clear();   //??
    ui->btnOpenCOM->setChecked(false);
    if(mysql.reOpen()==true)
    {
        connect(dateTime,SIGNAL(timeout()),this,SLOT(reOpenSql()));
    }
    if(initSerialPort()==true)
    {
        ui->comboBoxPort->setCurrentIndex(0);
        serial->setPortName(ui->comboBoxPort->currentText());
        ui->btnOpenCOM->setEnabled(true);
    }
}

void MainWindow::on_btnOpenCOM_toggled(bool checked)
{
    serial->close();
    result.clear();
    if(checked==true)
    {
        if(serial->open(QIODevice::ReadWrite)==true)
        {
            ui->btnOpenCOM->setText("关闭串口");
            labelSerial->setText(serial->portName()+"已打开");
            connect(serial,SIGNAL(readyRead()),this,SLOT(read_data()));
            comBoxEnabled(false);
        }
        else
        {
            ui->btnOpenCOM->setChecked(false);
        }
    }
     else
     {
            ui->btnOpenCOM->setText("打开串口");
            labelSerial->setText(serial->portName()+"已关闭");
            serial->close();
            ui->btnInsertData->setCheckable(false);
            comBoxEnabled(true);
     }
}
//读取串口数据
void MainWindow::read_data()
{
    QByteArray buf;
    QString str = "" ;
    buf = serial->readAll();
    if(!buf.isEmpty())
    {
        str = tr(buf);
        result += str;
        if(str.endsWith("\n"))
        {
            ui->textEdit->append(result);
            if(ifInsert==true&&mysql.isOpen())
            {
                mysql.insertSerial(result);
            }
            result.clear();
        }
    }
    buf.clear();
}

void MainWindow::on_btnExit_clicked()   //退出
{
    serial->close();
    MainWindow::close();
}

void MainWindow::on_comboBoxPort_currentIndexChanged(const QString &arg1)    //设置端口号？？？
{
    if(flag ==false)
    {
        serial->setPortName(arg1);
    }
}

void MainWindow::on_comboBoxBuad_currentIndexChanged(int index)  //设置波特率
{
    serial->setCBaud(index);
}

void MainWindow::on_comboBoxData_currentIndexChanged(int index)   //设置数据位
{
    serial->setCData(index);
}

void MainWindow::on_btnClear_clicked()    //清除窗口
{
    ui->textEdit->clear();
}

void MainWindow::on_btnClear_2_clicked()     //清除数据库
{
    mysql.clearAll();
}

void MainWindow::timeUpdate()      //时间更新
 {
     QDateTime time = QDateTime::currentDateTime();
     QString str = time.toString("yyyy-MM-dd hh:mm:ss dddd");
     labelTime->setText(str);
 }

void MainWindow::on_btnInsertData_toggled(bool checked)   //插入数据按钮
{
    ifInsert = checked;
    if(checked==true)
    {
        ui->btnInsertData->setText("结束插入");
        if(mysql.isOpen()==false)
        {
            QMessageBox::information(this,"数据库连接错误报告","数据库连接错误！请检查数据库连接情况。",QMessageBox::Ok);
            ui->btnInsertData->setChecked(false);
        }
    }
    else
    {
        ui->btnInsertData->setText("开始插入");
    }
}

void MainWindow::reOpenSql()
{
    if(mysql.isOpen())
    {
        labelSql->setText("Mysql数据库连接状态:已经连接。");
    }
    else
    {
        labelSql->setText("MySql数据库连接状态:无连接");
        ui->btnInsertData->setChecked(false);
        disconnect(dateTime,SIGNAL(timeout()),this,SLOT(reOpenSql()));
    }
}


void MainWindow::on_pushButton_clicked()
{
    sp=new ShowPlot();
    sp->show();
}
