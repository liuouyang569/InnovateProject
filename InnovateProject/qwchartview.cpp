#include "qwchartview.h"

#include    <QChartView>


void QWChartView::mousePressEvent(QMouseEvent *event)
{//鼠标左键按下，记录坐标
//    if (event->button()==Qt::LeftButton)
//        beginPoint=event->pos();
//    QChartView::mousePressEvent(event);
    QPoint  point;
    if (event->button()==Qt::LeftButton)
        point=event->pos();

    emit mousePressPoint(point);
}

void QWChartView::mouseMoveEvent(QMouseEvent *event)
{//鼠标移动事件
    QPoint  point;
    point=event->pos();

    emit mouseMovePoint(point);
    //QChartView::mouseMoveEvent(event);
}

//void QWChartView::mouseReleaseEvent(QMouseEvent *event)
//{
//    if (event->button()==Qt::LeftButton)
//    { //鼠标左键释放，获取矩形框的endPoint,进行缩放
//        endPoint=event->pos();
//        QRectF  rectF;
//        rectF.setTopLeft(this->beginPoint);
//        rectF.setBottomRight(this->endPoint);
//        this->chart()->zoomIn(rectF);
//    }
//    else if (event->button()==Qt::RightButton)
//        this->chart()->zoomReset(); //鼠标右键释放，resetZoom
//    QChartView::mouseReleaseEvent(event);
//}


QWChartView::QWChartView(QWidget *parent):QChartView(parent)
{
    this->setDragMode(QGraphicsView::RubberBandDrag);
//    this->setRubberBand(QChartView::RectangleRubberBand);//设置为矩形选择方式
//    this->setRubberBand(QChartView::VerticalRubberBand);
//    this->setRubberBand(QChartView::HorizontalRubberBand);

    this->setMouseTracking(true);//必须开启此功能
}

QWChartView::~QWChartView()
{

}
