#include "plotwave.h"

PlotWave::PlotWave()
{
    //chart.setTheme(QChart::ChartThemeBlueCerulean);//设置系统主题
    //chart.setTitle("SOP");//设置标题
    chart.setTitleFont(QFont("微软雅黑",10));
    chart.legend()->hide();
    QPen green(Qt::blue);
    green.setWidth(2);
    m_series.setPen(green);
    chart.addSeries(&m_series);
    chart.createDefaultAxes();
//    chart.setAxisX(&m_axis,&m_series);
//    chart.axisX()->setRange(0,100);
}

void PlotWave::DataPlotSop(double message)
{
    int i =  0;
    QVector<QPointF> oldData = m_series.pointsVector();
    QVector<QPointF> data;
    if (oldData.size() <= 110) {
        data = m_series.pointsVector();
    } else {
        /* 添加之前老的数据到新的vector中，不复制最前的数据，即每次替换前面的数据
         * 由于这里每次只添加1个数据，所以为1，使用时根据实际情况修改
         */
        for (i = 1; i < oldData.size(); ++i) {
            data.append(QPointF(i - 1 , oldData.at(i).y()));
        }
    }
    qint64 size = data.size();
    data.append(QPointF(i + size, message));
    m_series.replace(data);
}

void PlotWave::Reset()
{
    QVector<QPointF> data;
    m_series.replace(data);
}
