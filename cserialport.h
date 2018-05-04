#ifndef CSERIALPORT_H
#define CSERIALPORT_H

#include <QSerialPort>
#include <QSerialPortInfo>
class CSerialPort : public QSerialPort
{
public:
    CSerialPort();  //构造函数
    void Init();   //初始化函数
    void setCBaud(int index); //设置波特率
    void setCData(int index);  //设置数据位
    void setCParity(int index);   //设置校验位
    void setCStop();  //设置停止位
};

#endif // CSERIALPORT_H
