#include "plotwave_3.h"

PlotWave_3::PlotWave_3()
{
    chart.setTitleFont(QFont("微软雅黑",10));
    chart.legend()->hide();

    QPen green_1(Qt::blue);
    green_1.setWidth(1);
    series_1.setPen(green_1);
    chart.addSeries(&series_1);

    QPen green_2(Qt::red);
    green_2.setWidth(1);
    series_2.setPen(green_2);
    chart.addSeries(&series_2);

    QPen green_3(Qt::green);
    green_3.setWidth(1);
    series_3.setPen(green_3);
    chart.addSeries(&series_3);

    chart.createDefaultAxes();
}

void PlotWave_3::DataPlotSop(double message_1,double message_2,double message_3)
{
    //第一条线
    int i =  0;
    QVector<QPointF> oldData_1 = series_1.pointsVector();
    QVector<QPointF> oldData_2 = series_2.pointsVector();
    QVector<QPointF> oldData_3 = series_3.pointsVector();
    QVector<QPointF> data_1;
    QVector<QPointF> data_2;
    QVector<QPointF> data_3;
    if (oldData_1.size() <= 110) {
        data_1 = series_1.pointsVector();
        data_2 = series_2.pointsVector();
        data_3 = series_3.pointsVector();
    } else {
        /* 添加之前老的数据到新的vector中，不复制最前的数据，即每次替换前面的数据
         * 由于这里每次只添加1个数据，所以为1，使用时根据实际情况修改
         */
        for (i = 1; i < oldData_1.size(); ++i) {
            data_1.append(QPointF(i - 1 , oldData_1.at(i).y()));
            data_2.append(QPointF(i - 1 , oldData_2.at(i).y()));
            data_3.append(QPointF(i - 1 , oldData_3.at(i).y()));
        }
    }
    qint64 size = data_1.size();
    data_1.append(QPointF(i + size, message_1));
    data_2.append(QPointF(i + size, message_2));
    data_3.append(QPointF(i + size, message_3));
    series_1.replace(data_1);
    series_2.replace(data_2);
    series_3.replace(data_3);
}

void PlotWave_3::Reset()
{
    QVector<QPointF> data;
    series_1.replace(data);
    series_2.replace(data);
    series_3.replace(data);
}
