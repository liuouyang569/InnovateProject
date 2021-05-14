#include "plotball.h"
#define PI  3.14159265357989
#define N_num 10000

PlotBall::PlotBall()
{
    dataArray = new QScatterDataArray();//放坐标值
    dataArraySctter = new QScatterDataArray();//放坐标值

    graph3D = new Q3DScatter();
    graphContainer = QWidget::createWindowContainer(graph3D); //Q3DBars继承自QWindow，必须如此创建

    //设置存储坐标轴的序列
    QScatterDataProxy *proxy = new QScatterDataProxy(); //数据代理
    series = new QScatter3DSeries(proxy);  //创建序列
    series->setItemLabelFormat("(@xLabel @yLabel @zLabel)");
    series->setMeshSmooth(true);
    graph3D->addSeries(series);
    series->setBaseColor(Qt::black);//设置离散点颜色
    graph3D->setVisible(false);


    //设置存储离散点的序列
    QScatterDataProxy *proxyScatter = new QScatterDataProxy(); //数据代理   散点
    seriesScatter = new QScatter3DSeries(proxyScatter);  //创建序列
    seriesScatter->setMeshSmooth(true);
    graph3D->addSeries(seriesScatter);
    seriesScatter->setBaseColor(Qt::red);//设置离散点颜色

    //创建坐标轴
    QValue3DAxis *axisX=new QValue3DAxis;
    axisX->setTitle("Axis X");
    axisX->setTitleVisible(true);
    axisX->setRange(-2,2);
    //axisX->setAutoAdjustRange(true);
    graph3D->setAxisX(axisX);

    QValue3DAxis *axisY=new QValue3DAxis;
    axisY->setTitle("Axis Z");
    axisY->setTitleVisible(true);
    axisY->setRange(-2,2);
    graph3D->setAxisY(axisY);

    QValue3DAxis *axisZ=new QValue3DAxis;
    axisZ->setTitle("Axis Y");
    axisZ->setTitleVisible(true);
    axisZ->setRange(-2,2);
    graph3D->setAxisZ(axisZ);

    //设置离散点序列和坐标轴序列一些基本属性s
    graph3D->activeTheme()->setLabelBackgroundEnabled(false);
    series->setMesh(QAbstract3DSeries::MeshCylinder); //MeshPoint, MeshCylinder    MeshSphere可以设置为圆球
    series->setItemSize(0.05);//default 0. value 0~1 控制相对大小
    seriesScatter->setMesh(QAbstract3DSeries::MeshSphere);
    seriesScatter->setItemSize(0.1);
    //放置在外成为全局变量
    //QScatterDataArray *dataArray = new QScatterDataArray();//放坐标值

    dataArray->resize(6100);
    ptrToDataArray = &dataArray->first();//获得首地址，依次填入坐标值

    dataArraySctter->resize(N_num);
    ptrToDataArraySctter = &dataArraySctter->first();//获得首地址，依次填入坐标值

    //graph3D->setShadowQuality(QAbstract3DGraph::ShadowQualityNone);
    InitLabel();
    //3D图 水平 垂直 缩放三个参数控制
    graph3D->scene()->activeCamera()->setCameraPosition(-43,25,200);
    graph3D->activeTheme()->setBackgroundEnabled(false);    //去除背景黑点
}

QVector3D PlotBall::InitLabel()
{
    double x,y,z,theta = 0;
//    for(theta=0;theta<=2*PI;theta+=0.002*PI)
//    {
//        x = qCos(theta);
//        y = qSin(theta);
//        ptrToDataArray->setPosition(QVector3D(x,y,0));    //添加坐标点
//        ptrToDataArray++;
//        ptrToDataArray->setPosition(QVector3D(x,0,y));    //添加坐标点
//        ptrToDataArray++;
//        ptrToDataArray->setPosition(QVector3D(0,x,y));    //添加坐标点
//        ptrToDataArray++;
//    }//指针加1
    for(theta=-1.5;theta<=1.5;theta+=0.002)
    {
        x = theta;
        y = 0;
        ptrToDataArray->setPosition(QVector3D(x,y,0));    //添加坐标点
        ptrToDataArray++;
        ptrToDataArray->setPosition(QVector3D(y,0,x));    //添加坐标点
        ptrToDataArray++;
        ptrToDataArray->setPosition(QVector3D(0,x,y));    //添加坐标点
        ptrToDataArray++;
    }//指针加1
    series->dataProxy()->resetArray(dataArray);
}

QVector3D PlotBall::randVector(double x,double y,double z)
{
    //double x,y,z;
    //series->setBaseColor(Qt::red);
    //qDebug()<<i;
    ptrToDataArraySctter->setPosition(QVector3D(x,z,y));    //添加坐标点形式为(x,z,y)
    ptrToDataArraySctter++;

    seriesScatter->dataProxy()->resetArray(dataArraySctter);       //画图命令
}

void PlotBall::Reset()
{
    ptrToDataArraySctter = &dataArraySctter->first();
    for(int i=0;i<N_num;i++)
    {
        ptrToDataArraySctter->setPosition(QVector3D(0,0,0));    //添加坐标点
        ptrToDataArraySctter++;
    }
    seriesScatter->dataProxy()->resetArray(dataArraySctter);
    ptrToDataArraySctter = &dataArraySctter->first();
}
