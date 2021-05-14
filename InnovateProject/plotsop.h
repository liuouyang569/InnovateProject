#ifndef PLOTSOP_H
#define PLOTSOP_H
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
#define PI  3.14159265357989
#define N_num 10000

QT_CHARTS_USE_NAMESPACE

class plotSop
{
public:
    plotSop();
    QChart chart;
    QSplineSeries m_series;
    QSplineSeries m_background;  //背景参照圆
    QStringList m_titles;
    QValueAxis m_axis;
    void DataPlotSop(double azimuth,double ellipticity);    //二维图画图函数
    void Reset();

    double data[N_num][3];
    int num;//计算点的数量
};

#endif // PLOTSOP_H
