#ifndef PLOTWAVE_3_H
#define PLOTWAVE_3_H

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

QT_CHARTS_USE_NAMESPACE

class PlotWave_3
{
public:
    PlotWave_3();
    QChart chart;
    QSplineSeries series_1;
    QSplineSeries series_2;
    QSplineSeries series_3;
    QStringList m_titles;
    QValueAxis m_axis;
    void DataPlotSop(double message_1,double message_2,double message_3); //二维图画图函数
    void Reset();
};

#endif // PLOTWAVE_3_H
