#ifndef WIDGET_H
#define WIDGET_H

#include <QWidget>
#include <QList>
#include <QString>
#include <QStandardItem>  //表格
#include <QStandardItem>  //表格单元格
#include <QtCharts/QChartView>//显示图表
#include <QtCharts/QLineSeries>//线系列
#include <QDoubleSpinBox>
#include <QGridLayout>
#include <QtCharts/QSplineSeries>
#include <QtCharts/QValueAxis>
#include "QDebug"
#include "qmath.h"
#include "QValueAxis"
#include "QDateTimeAxis"
#include "QRandomGenerator"
#include <QWidget>
#include <QUdpSocket>
#include <QThread>
#include <QHostAddress>
#include "receivethread.h"
#include "plotball.h"
#include "plotwave.h"
#include "udpclass.h"
#include "plotwave_3.h"
#include "qwchartview.h"
#include "plotsop.h"

#include    <QtCharts>  //必须这么设置
QT_CHARTS_USE_NAMESPACE     //必须这么设置

const int N = 400; //采样点数

QT_BEGIN_NAMESPACE
namespace Ui { class Widget; }
QT_END_NAMESPACE


class Widget : public QWidget
{
    Q_OBJECT

public:
    Widget(QWidget *parent = nullptr);
    ~Widget();
    void switchPage();//切换函数

//第一页图的变量
public:
    PlotBall plotball;// 三维图所需
    PlotWave WaveSop;
    plotSop Sop;
    void InitSop();
    void Init3D();
    void setValue(double s1,double s2,double s3,double DOP,double DOLP,double DOCP,double azimuth,double ellipticity,double power);
    double data[N];
    int flag;//系统开始暂停的标志
private:
    Ui::Widget *ui;
private slots:
    void btnBegin();
    void btnReset();
    void Algorithm(double mesage);
signals:
    void SignalPlotSop(double message);//接收处理信号


//第二页所需
public:
    QString cnt;//保存数据所用字符串
    QList<QString> stu_lines;  //容器写法前面是容器的类型后面是容器内部单个数据的类型
    QStandardItemModel * model;
    void InitItemModel();
    QString file_path;
private slots:
    void FunctionChoosepath();      //选择文件保存路径槽函数
    void FunctionSave();            //保存文件槽函数
    void FunctionChoosepath_Read();      //选择文件读取路径槽函数
    void FunctionRead();                //读取文件槽函数
//第三页所需
public:
      PlotWave_3 WaveStokes;
      PlotWave_3 WaveDop;
      void InitWaveStokes();
      void InitWaveDop();
      void InitItemStokes();
      void InitItemDop();
      QList<QString> stu_lines_stokes;  //容器写法前面是容器的类型后面是容器内部单个数据的类型
      QStandardItemModel * modelStokes;

      QList<QString> stu_lines_dop;  //容器写法前面是容器的类型后面是容器内部单个数据的类型
      QStandardItemModel * modelDop;

      int flag_stokes;
      int flag_dop;
signals:
    void mouseMovePoint(QPoint); //鼠标移动信号，在mouseMoveEvent()事件中触发
private slots:
    void mouseMovePointStokes(QPoint); //stokes界面鼠标移动事件，自定义槽函数
    void mouseMovePointDop(QPoint);    //Dop界面鼠标移动事件，自定义槽函数
    void mousePressStokes(QPoint);     //鼠标点击事件
    void mousePressDop(QPoint);
//第四页所需


// UDP所需
public:
    UDPclass UdpSignal;
};
#endif // WIDGET_H
