﻿#ifndef QWCHARTVIEW_H
#define QWCHARTVIEW_H


#include    <QtCharts>  //必须这么设置
QT_CHARTS_USE_NAMESPACE     //必须这么设置


class QWChartView : public QChartView
{
    Q_OBJECT

private:
    QPoint  beginPoint; //选择矩形区的起点
    QPoint  endPoint;  //选择矩形区的终点

protected:
    void mouseMoveEvent(QMouseEvent *event); //鼠标移动
    void mousePressEvent(QMouseEvent *event); //鼠标左键按下

public:
    explicit QWChartView(QWidget *parent = 0);
    ~QWChartView();

signals:
    void mouseMovePoint(QPoint point); //鼠标移动信号，在mouseMoveEvent()事件中触发
    void mousePressPoint(QPoint point); //鼠标移动信号，在mouseMoveEvent()事件中触发
};

#endif // QWCHARTVIEW_H
