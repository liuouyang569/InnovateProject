#ifndef PLOTBALL_H
#define PLOTBALL_H

#include <QHostAddress>
#include <QWidget>
#include "receivethread.h"
#include  <QtDataVisualization>
#include <QGridLayout>



using namespace QtDataVisualization;

class PlotBall
{
public:
    PlotBall();
    void Reset();

    QWidget     *graphContainer;//
    Q3DScatter  *graph3D;       //散点图
    QScatter3DSeries *series;  //散点序列
    QScatter3DSeries *seriesScatter;  //散点序列

    QScatterDataArray *dataArray;//放坐标值
    QScatterDataItem *ptrToDataArray;
    QScatterDataArray *dataArraySctter;//放坐标值
    QScatterDataItem *ptrToDataArraySctter;
    void    iniGraph3D(); //初始化绘图
    QVector3D InitLabel();//初始化坐标轴
    QVector3D randVector(double x,double y,double z);
private slots:


private:
//三维图所需:

};

#endif // PLOTBALL_H
