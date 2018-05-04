#ifndef SHOWPLOT_H
#define SHOWPLOT_H

#include <QMainWindow>
#include "./lib/qcustomplot.h"
#include "mydbadapter2.h"
#include <QVBoxLayout>
#include <QGridLayout>
#include <QLabel>
#include <QWidget>

//#define foreach Q_FOREACH

class QCustomPlot;

class ShowPlot : public QMainWindow
{
    Q_OBJECT

public:
    ShowPlot(QWidget *parent = 0);
    bool addAllData(QDateTime dateTime);
    ~ShowPlot();

private:
    QWidget *cenWidget;
    QCustomPlot *methonePlot;
    QCustomPlot *ammoniaPlot;
    QCustomPlot *hydrothionPlot;
    QTabWidget *tabWidget;

    QLabel *labelDate;
    QDateEdit *date;
    QPushButton *btnUpdate;
    myDBAdapter2 mysql2;

    QCPItemTracer *m_sameTimeTracer;
    QCPItemText *m_sameTimeTextTip;
    QCustomPlot *SameTimeCompareCustomPlot;
    void initPlots();
    void initItems();
    void connectSlots();
    //void setCH4Data(QDate date);
    void setPlotData(QDate date,QCustomPlot *customPlot,QString gasTable);

private slots:
    void updateDate(QDate date);
    void currentWidgetChangeSlot(int index);
    void updateDate();
    void mousePressEventSlot(QMouseEvent *e);
//    MyDaiag *dialog; //添加私有成员，为一个dailog（窗口）的指针 DJH

};

#endif // SHOWPLOT_H
