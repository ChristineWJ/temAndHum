#include "showplot.h"

ShowPlot::ShowPlot(QWidget *parent)
    : QMainWindow(parent)
{
    cenWidget = new QWidget(this);

    tabWidget = new QTabWidget(cenWidget);
    methonePlot = new QCustomPlot();
    ammoniaPlot = new QCustomPlot();
    hydrothionPlot = new QCustomPlot();

    labelDate = new QLabel(cenWidget);
    date = new QDateEdit(QDate::currentDate(),cenWidget);
    btnUpdate = new QPushButton(cenWidget);
    QGridLayout *gridLayout = new QGridLayout(cenWidget);

    date->setCalendarPopup(true);
    labelDate->setText("选择日期："+date->date().toString());
    btnUpdate->setText("刷新图像");

    initPlots();
    tabWidget->addTab(methonePlot,"甲烷浓度");
    tabWidget->addTab(ammoniaPlot,"氨气浓度");
    tabWidget->addTab(hydrothionPlot,"硫化氢浓度");
    initItems();

    gridLayout->addWidget(labelDate,0,0);
    gridLayout->addWidget(date,0,1);
    gridLayout->addWidget(btnUpdate,0,2);
    gridLayout->addWidget(new QLabel(cenWidget),0,3);
    gridLayout->addWidget(new QLabel(cenWidget),0,4);
    gridLayout->addWidget(tabWidget,1,0,1,5);

    connectSlots();
    this->setCentralWidget(cenWidget);
    this->resize(1000,700);
}

void ShowPlot::initPlots()
{
    //xAxis,设置坐标轴样式
    //myPlot->axisRect()->setupFullAxesBox();

    QSharedPointer<QCPAxisTickerTime> timeTicker(new QCPAxisTickerTime);
    timeTicker->setTimeFormat("%h:%m:%s");

    methonePlot->xAxis->setTicker(timeTicker);
    methonePlot->xAxis->setRange(0,60*60*25);
    methonePlot->xAxis->setSubTicks(true);
    methonePlot->yAxis->setRange(500, 1000);
    methonePlot->xAxis->setLabel("时间");
    methonePlot->yAxis->setLabel("浓度");
    methonePlot->setAutoAddPlottableToLegend(true);
    //connect(methonePlot->xAxis, SIGNAL(rangeChanged(QCPRange)), methonePlot->xAxis2, SLOT(setRange(QCPRange)));
    //connect(methonePlot->yAxis, SIGNAL(rangeChanged(QCPRange)), methonePlot->yAxis2, SLOT(setRange(QCPRange)));
    //methonePlot->setInteractions(QCP::iSelectPlottables| QCP::iSelectLegend);

    ammoniaPlot->xAxis->setTicker(timeTicker);
    ammoniaPlot->xAxis->setRange(0,60*60*25);
    ammoniaPlot->xAxis->setSubTicks(true);
    ammoniaPlot->yAxis->setRange(0, 100);
    ammoniaPlot->xAxis->setLabel("时间");
    ammoniaPlot->yAxis->setLabel("浓度");
    ammoniaPlot->setAutoAddPlottableToLegend(true);
    //connect(ammoniaPlot->xAxis, SIGNAL(rangeChanged(QCPRange)), ammoniaPlot->xAxis2, SLOT(setRange(QCPRange)));
    //connect(ammoniaPlot->yAxis, SIGNAL(rangeChanged(QCPRange)), ammoniaPlot->yAxis2, SLOT(setRange(QCPRange)));
    //ammoniaPlot->setInteractions(QCP::iSelectPlottables | QCP::iSelectLegend);

    hydrothionPlot->xAxis->setTicker(timeTicker);
    hydrothionPlot->xAxis->setRange(0,60*60*25);
    hydrothionPlot->xAxis->setSubTicks(true);
    hydrothionPlot->yAxis->setRange(0, 100);
    hydrothionPlot->xAxis->setLabel("时间");
    hydrothionPlot->yAxis->setLabel("浓度");
    hydrothionPlot->setAutoAddPlottableToLegend(true);
    //connect(hydrothionPlot->xAxis, SIGNAL(rangeChanged(QCPRange)), hydrothionPlot->xAxis2, SLOT(setRange(QCPRange)));
    //connect(hydrothionPlot->yAxis, SIGNAL(rangeChanged(QCPRange)), hydrothionPlot->yAxis2, SLOT(setRange(QCPRange)));
    //hydrothionPlot->setInteractions(QCP::iSelectPlottables);

    setPlotData(date->date(),this->methonePlot,"gas_CH4");
    setPlotData(date->date(),this->ammoniaPlot,"gas_NH3");
    setPlotData(date->date(),this->hydrothionPlot,"gas_H2S");
}

void ShowPlot::initItems()
{
    SameTimeCompareCustomPlot = (QCustomPlot*)this->tabWidget->currentWidget();
    m_sameTimeTracer = new QCPItemTracer(SameTimeCompareCustomPlot);
    m_sameTimeTextTip = new QCPItemText(SameTimeCompareCustomPlot);

    m_sameTimeTracer->setPen(QColor(255,255,255));
    m_sameTimeTracer->setBrush(QBrush(QColor(255,0,0),Qt::SolidPattern));
    m_sameTimeTracer->setStyle(QCPItemTracer::tsCircle);
    m_sameTimeTracer->setSize(10);
    m_sameTimeTracer->setVisible(false);

    //m_sameTimeTextTip->setParent(SameTimeCompareCustomPlot);
    m_sameTimeTextTip->setPositionAlignment(Qt::AlignTop|Qt::AlignHCenter);
    m_sameTimeTextTip->position->setType(QCPItemPosition::ptAbsolute);
    QFont font;
    font.setPixelSize(15);
    m_sameTimeTextTip->setFont(font); // make font a bit larger
    m_sameTimeTextTip->setPen(QPen(Qt::red)); // show black border around text
    m_sameTimeTextTip->setBrush(Qt::white);
    m_sameTimeTextTip->setVisible(false);
}

void ShowPlot::connectSlots()
{
    connect(date,SIGNAL(dateChanged(QDate)),this,SLOT(updateDate(QDate)));
    connect(btnUpdate,SIGNAL(clicked()),this,SLOT(updateDate()));
    connect(tabWidget,SIGNAL(currentChanged(int)),this,SLOT(currentWidgetChangeSlot(int)));
    connect(methonePlot,SIGNAL(mousePress(QMouseEvent*)),this,SLOT(mousePressEventSlot(QMouseEvent*)));
    connect(ammoniaPlot,SIGNAL(mousePress(QMouseEvent*)),this,SLOT(mousePressEventSlot(QMouseEvent*)));
    connect(hydrothionPlot,SIGNAL(mousePress(QMouseEvent*)),this,SLOT(mousePressEventSlot(QMouseEvent*)));
}

ShowPlot::~ShowPlot()
{
    delete cenWidget;
}


void ShowPlot::updateDate(QDate date)
{
    labelDate->setText("选择日期："+date.toString());
    setPlotData(date,this->methonePlot,"gas_CH4");
    setPlotData(date,this->ammoniaPlot,"gas_NH3");
    setPlotData(date,this->hydrothionPlot,"gas_H2S");
}


void ShowPlot::updateDate()
{
    //DJH
    //QMessageBox::information(this, QString::fromLocal8Bit("Warning"),QString::fromLocal8Bit("wahahah"));


    //DJH
    setPlotData(this->date->date(),this->methonePlot,"gas_CH4");
    setPlotData(this->date->date(),this->ammoniaPlot,"gas_NH3");
    setPlotData(this->date->date(),this->hydrothionPlot,"gas_H2S");
    //QTimer::singleShot(1000,this,SLOT(updateDate()));
}

void ShowPlot::currentWidgetChangeSlot(int index)
{
    SameTimeCompareCustomPlot->removeItem(m_sameTimeTracer);
    SameTimeCompareCustomPlot->removeItem(m_sameTimeTextTip);
    SameTimeCompareCustomPlot->replot();

    this->initItems();

}
void ShowPlot::mousePressEventSlot(QMouseEvent *e)
{
    QCPGraph *graph = qobject_cast<QCPGraph*>(SameTimeCompareCustomPlot->plottableAt(e->pos(),true));
    QPointF pressPos(0,0);//跟踪鼠标点击事件点击位置
    QRect rect(0,0,1,1);
    double key = 0,value = 0;
    if(graph)
        {
            QPoint p;
            double posKey;
            p.setX(e->pos().x());
            p.setY(e->pos().y());

            QVector<QCPGraphData>::iterator data = graph->data()->begin();
            for(;data!=graph->data()->end();data++)
            {
                key = data->key;
                value = data->value;
                posKey = SameTimeCompareCustomPlot->xAxis->coordToPixel(key);
                if(qAbs(posKey-e->pos().x())<=10)
                {
                    double posx = graph->keyAxis()->coordToPixel(key);
                    double posy = graph->valueAxis()->coordToPixel(value);
                    rect.setRect(posx-10,posy-10,21,21);
                    if(!rect.contains(e->pos()))
                        continue;
                    else
                        break;
                }
                if(posKey-e->pos().x()>10)
                    break;
            }
            if(!graph->realVisibility())
            {
                m_sameTimeTracer->setVisible(false);
                pressPos.setX(0);
                pressPos.setY(0);
                SameTimeCompareCustomPlot->replot();
            }else if(rect.contains(e->pos()))
            {
                m_sameTimeTracer->setGraph(graph);
                m_sameTimeTracer->setGraphKey(key);
                m_sameTimeTracer->setVisible(true);
                pressPos.setX(key);
                pressPos.setY(value);
                SameTimeCompareCustomPlot->replot();
            }else
            {
                if(m_sameTimeTracer->visible())
                {
                    m_sameTimeTracer->setVisible(false);
                    pressPos.setX(0);
                    pressPos.setY(0);
                    SameTimeCompareCustomPlot->replot();
                }
            }
        }else
        {
            if(m_sameTimeTracer != NULL)
            {
                if(m_sameTimeTracer->visible())
                {
                    m_sameTimeTracer->setVisible(false);
                    pressPos.setX(0);
                    pressPos.setY(0);
                    SameTimeCompareCustomPlot->replot();
                }
            }
        }

        if(pressPos.x()!=0 && pressPos.y()!=0)
        {
            m_sameTimeTextTip->setText("X轴: "+QString::number(pressPos.x()) +"\nY轴: "+QString::number(pressPos.y(),'f',3)+"ppm");
            m_sameTimeTextTip->position->setCoords(e->pos().x()-30,e->pos().y()+15);
            m_sameTimeTextTip->setVisible(true);
            SameTimeCompareCustomPlot->replot();
        }else
        {
            if(m_sameTimeTextTip != NULL)
            {
                m_sameTimeTextTip->setVisible(false);
                SameTimeCompareCustomPlot->replot();
            }
        }
}

/*void ShowPlot::setCH4Data(QDate date)
{
    methonePlot->clearGraphs();
    QList<gasView> list;
    QVector<int> num;
    list = mysql2.selectCH4(date);
    num = mysql2.selectPNumber();
    for(int i=0; i<list.length(); i++)
    {
        qDebug()<<i<<" "<<list[i].PNumber<<" "<<list[i].GasConcentration<<" "<<list[i].GasTime.toString()<<endl;
    }

    for(int i=0; i<num.length(); i++)
    {
        methonePlot->addGraph();
        QColor color(20+200/4.0*i,70*(1.6-i/4.0), 150, 150);
        methonePlot->graph()->setLineStyle(QCPGraph::lsLine);
        methonePlot->graph()->setPen(QPen(color.lighter(200)));
        methonePlot->graph()->setBrush(QBrush(color));

    }

    double x,y;
    QTime time;
    for(int i=0; i<num.length(); i++)
    {
        for(int j=0; j<list.length(); j++)
        {
            if(list[j].PNumber==num[i])
            {
                time = list[j].GasTime.time();
                x = time.hour()*60*60+time.minute()*60+time.second();
                y = list[j].GasConcentration.toDouble();
                methonePlot->graph(i)->addData(x,y);
            }
        }
        methonePlot->graph(i)->setName(QString("节点%1").arg(QString::number(num[i])));
    }
    methonePlot->legend->setVisible(true);
    methonePlot->legend->setBrush(QColor(255, 255, 255, 150));
    methonePlot->replot();
}*/

void ShowPlot::setPlotData(QDate date, QCustomPlot *customPlot, QString gasTable)
{
    customPlot->clearGraphs();
    QList<gasView> list;
    QVector<int> num;
    list = mysql2.selectGas(date,gasTable);
    num = mysql2.selectPNumber();
    /*for(int i=0; i<list.length(); i++)
    {
        qDebug()<<i<<" "<<list[i].PNumber<<" "<<list[i].GasConcentration<<" "<<list[i].GasTime.toString()<<endl;
    }*/

    for(int i=0; i<num.length(); i++)
    {
        customPlot->addGraph();
        QColor color(20+200/4.0*i,70*(1.6-i/4.0), 150, 150);
        customPlot->graph()->setLineStyle(QCPGraph::lsLine);
        customPlot->graph()->setPen(QPen(color.lighter(100)));
        customPlot->graph()->setBrush(QBrush(color));
        customPlot->graph()->setScatterStyle(QCPScatterStyle(QCPScatterStyle::ssStar,10));

    }

    double x,y;
    QTime time;
    for(int i=0; i<num.length(); i++)
    {
        for(int j=0; j<list.length(); j++)
        {
            if(list[j].PNumber==num[i])
            {
                time = list[j].GasTime.time();
                x = time.hour()*60*60+time.minute()*60+time.second();
                y = list[j].GasConcentration.toDouble();
                customPlot->graph(i)->addData(x,y);
            }
        }
        customPlot->graph(i)->setName(QString("节点%1").arg(QString::number(num[i])));
    }
    //customPlot->rescaleAxes(true);
    customPlot->legend->setVisible(true);
    customPlot->legend->setBrush(QColor(255, 255, 255, 150));

    customPlot->replot();
}

