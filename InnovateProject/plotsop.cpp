#include "plotsop.h"
plotSop::plotSop()
{
    //chart.setTheme(QChart::ChartThemeBlueCerulean);//设置系统主题
    //chart.setTitle("SOP");//设置标题
    chart.setTitleFont(QFont("微软雅黑",10));
    chart.legend()->hide();

    QPen green(Qt::red);                   //分别设置背景参照圆的序列和椭圆的序列颜色线宽等等
    green.setWidth(3);
    m_series.setPen(green);
    chart.addSeries(&m_series);
    chart.createDefaultAxes();

    QPen temp(Qt::blue);
    temp.setWidth(5);
    m_background.setPen(temp);
    chart.addSeries(&m_background);
    chart.createDefaultAxes();

    num = 0;
    QVector<QPointF> data_back;
    double theta = 0;
    for(theta = 0;theta <= 2*PI; theta += 0.001*PI)
    {
        double x = cos(theta);
        double y = sin(theta);
        data_back.append(QPointF(x,y));
    }
    m_background.replace(data_back);
    for(double theta = 0;theta < 2*PI;theta += 0.001*PI)         //首先形成一个单位圆
    {
        data[num][0] = 0.97*cos(theta);
        data[num][1] = 0.97*sin(theta);
        data[num][2] = 0;
        num++;
    }
}

void plotSop::DataPlotSop(double azimuth,double ellipticity)
{
    int i = 0,j = 0;
    double temp[N_num][3],result[N_num][3],tmp;
    ellipticity = ellipticity*2;
    if(ellipticity > -5 && ellipticity < 5 )
        ellipticity = 0;
//    ellipticity = 45;
//    azimuth = 20;
    tmp = ellipticity;
    ellipticity = azimuth;
    azimuth = tmp;
    azimuth = azimuth/360*2*PI;
    ellipticity = ellipticity/360*2*PI;
    double Matrix_x[3][3] = {{1,0,0},{0,cos(azimuth),-sin(azimuth)},{0,sin(azimuth),cos(azimuth)}};
    double Matrix_y[3][3] = {{cos(ellipticity),0,sin(ellipticity)},{0,1,0},{-sin(ellipticity),0,cos(ellipticity)}};
    //tatic int jishu= 0;  //调试bug代码
    //qDebug()<< jishu++;
    //qDebug()<< num;
    for(i = 0;i < num;i++)                                                     //矩阵乘法,坐标旋转
    {
        for(j = 0;j < 3;j++)
        {
           temp[i][j] =  data[i][0]*Matrix_x[0][j] + data[i][1]*Matrix_x[1][j] + data[i][2]*Matrix_x[2][j];
        }
    }
    for(i = 0;i < num;i++)                                                     //矩阵乘法，坐标旋转
    {
        for(j = 0;j < 3;j++)
        {
           result[i][j] =  temp[i][0]*Matrix_y[0][j] + temp[i][1]*Matrix_y[1][j] + temp[i][2]*Matrix_y[2][j];
        }
    }
    QVector<QPointF> data_sop;
    //注意，一定是小于num，不是小于等于，预定义给了10000的空间，后面为零，如是小于等于num，则在矩阵乘法中会无缘无故多乘上一个0
    //结果导致图像中会平白无故出现一条白线，此处bug浪费我一个小时！！！
    for(int i = 0;i < num;i++)
    {
        data_sop.append(QPointF(result[i][0],result[i][2]));
    }
    m_series.replace(data_sop);
}
void plotSop::Reset()
{
    QVector<QPointF> data;
    m_series.replace(data);
}
