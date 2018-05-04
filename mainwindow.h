#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <cserialport.h>
#include "mydbadapter.h"
#include <QLabel>
#include <showplot.h>   //必须引用类B的头文件
namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();

private slots:
    void on_action_triggered();

    void on_btnOpenCOM_toggled(bool checked);

    void on_btnExit_clicked();

    void read_data();  //读取串口数据槽函数

    void on_comboBoxPort_currentIndexChanged(const QString &arg1);  //修改串口号

    void on_comboBoxBuad_currentIndexChanged(int index);   //修改波特率

    void on_comboBoxData_currentIndexChanged(int index);//修改数据位

    void on_btnClear_clicked();  //清除窗口

    void on_btnClear_2_clicked();   //清除数据库

    void timeUpdate();

    void reOpenSql();

    void on_btnInsertData_toggled(bool checked);
    //void on_comboBoxPort_activated(const QString &arg1);

    void on_pushButton_clicked();

private:
    Ui::MainWindow *ui;
    ShowPlot *sp;   //创建类B的指针
    bool flag;
    bool ifInsert;
    QString result;
    CSerialPort *serial;
    myDBAdapter mysql;
    QTimer *dateTime;
    QLabel *labelTime;
    QLabel *labelSql;
    QLabel *labelSerial;
    bool initSerialPort();
    void comBoxEnabled(bool x);

};

#endif // MAINWINDOW_H
