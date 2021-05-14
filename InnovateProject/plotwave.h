#ifndef PLOTWAVE_H
#define PLOTWAVE_H

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

class PlotWave
{
public:
    PlotWave();
    QChart chart;
    QSplineSeries m_series;
    QStringList m_titles;
    QValueAxis m_axis;
    void DataPlotSop(double message);    //二维图画图函数
    void Reset();
};

#endif // PLOTWAVE_H
