#include "cserialport.h"
#include "qserialport.h"
#include "qserialportinfo.h"

CSerialPort::CSerialPort()
{
    Init();
}

void CSerialPort::Init()
{
    this->setBaudRate(QSerialPort::Baud115200);  //波特率默认为15200
    this->setDataBits(QSerialPort::Data8); //数据位默认为8
    this->setParity(QSerialPort::NoParity);    //默认无奇偶校验
    this->setStopBits(QSerialPort::OneStop);   //默认无停止位
    this->setFlowControl(QSerialPort::NoFlowControl);  //流控制：无
}

void CSerialPort::setCBaud(int index)
{
    switch(index){
    case 0:
        this->setBaudRate(QSerialPort::Baud115200);
        break;
    case 1:
        this->setBaudRate(QSerialPort::Baud9600);
        break;
    default:
        break;
    }
}

void CSerialPort::setCParity(int index)   //设置奇偶校验？？？
{
    switch(index){
    case 0 :
        this->parityChanged(QSerialPort::NoParity);
        break;
    default:
        break;
    }
}

void CSerialPort::setCData(int index)
{
    switch(index){
    case 0:
        this->dataBitsChanged(QSerialPort::Data8);
        break;
    case 1:
        this->dataBitsChanged(QSerialPort::Data7);
        break;
    default:
        break;
    }
}
