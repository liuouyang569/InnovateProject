#include "widget.h"
#include "ui_widget.h"
#include "plotball.h"
#include "plotwave.h"
#include <QChartView>
#include "udpsingal.h"
#include <QDebug>
#define PI  3.14159265357989

Widget::Widget(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::Widget)
{
    ui->setupUi(this);
    //选择页面槽函数绑定
    connect(ui->btnShowData,&QPushButton::clicked,this,&Widget::switchPage);
    connect(ui->btnSaveData,&QPushButton::clicked,this,&Widget::switchPage);
    connect(ui->btnParameter,&QPushButton::clicked,this,&Widget::switchPage);
    //第一页二维图以及3D图
    InitSop();
    Init3D();
    flag = 0;    //系统开始暂停标志
    //第一页按钮槽函数绑定
    connect(ui->btnBegin,&QPushButton::clicked,this,&Widget::btnBegin);
    connect(ui->btnReset,&QPushButton::clicked,this,&Widget::btnReset);
    //第二页初始化表格
    this->model = new QStandardItemModel;
    InitItemModel();
    connect(ui->btnChoose,&QPushButton::clicked,this,&Widget::FunctionChoosepath);
    connect(ui->btnSaveFile,&QPushButton::clicked,this,&Widget::FunctionSave);
    connect(ui->btnChoose_Read,&QPushButton::clicked,this,&Widget::FunctionChoosepath_Read);
    connect(ui->btnReadFile,&QPushButton::clicked,this,&Widget::FunctionRead);
    //第三页图形
    flag_dop = 0;
    flag_stokes = 0;
    InitWaveStokes();
    InitWaveDop();
    this->modelStokes = new QStandardItemModel;
    this->modelDop = new QStandardItemModel;
    InitItemStokes();
    InitItemDop();
    this->setMouseTracking(true);//必须开启此功能
    QObject::connect(ui->widgetWaveStokes,SIGNAL(mouseMovePoint(QPoint)),this, SLOT(mouseMovePointStokes(QPoint)));  //鼠标移动事件
    QObject::connect(ui->widgetWaveDop,SIGNAL(mouseMovePoint(QPoint)),this, SLOT(mouseMovePointDop(QPoint)));  //鼠标移动事件
    QObject::connect(ui->widgetWaveStokes,SIGNAL(mousePressPoint(QPoint)),this, SLOT(mousePressStokes(QPoint)));  //鼠标移动事件
    QObject::connect(ui->widgetWaveDop,SIGNAL(mousePressPoint(QPoint)),this, SLOT(mousePressDop(QPoint)));  //鼠标移动事件
    //第四页
}

Widget::~Widget()
{
    delete ui;
}

void Widget::switchPage(){
    QPushButton *button = qobject_cast<QPushButton*>(sender());//得到按下的按钮的指针
    if(button==ui->btnShowData)
        ui->stackedWidget->setCurrentIndex(0);//根据按下的button按索引显示相应的页面
    else if(button==ui->btnSaveData)
        ui->stackedWidget->setCurrentIndex(1);
    else if(button==ui->btnParameter)
        ui->stackedWidget->setCurrentIndex(2);
}

void Widget::InitItemModel()
{
    this->model->clear();//清楚表格，每次射之前调用该函数
    //设置表头
    this->model->setHorizontalHeaderItem(0,new QStandardItem("S1"));
    this->model->setHorizontalHeaderItem(1,new QStandardItem("S2"));
    this->model->setHorizontalHeaderItem(2,new QStandardItem("S3"));
    this->model->setHorizontalHeaderItem(3,new QStandardItem("DOP"));
    this->model->setHorizontalHeaderItem(4,new QStandardItem("DOLP"));
    this->model->setHorizontalHeaderItem(5,new QStandardItem("DOCP"));
    this->model->setHorizontalHeaderItem(6,new QStandardItem("方位角"));
    this->model->setHorizontalHeaderItem(7,new QStandardItem("椭圆度"));
    this->model->setHorizontalHeaderItem(8,new QStandardItem("PER"));

    this->ui->tableView->setModel(model);
    this->ui->tableView->setColumnWidth(0,80);
    this->ui->tableView->setColumnWidth(1,80);
    this->ui->tableView->setColumnWidth(2,80);
    this->ui->tableView->setColumnWidth(3,80);
    this->ui->tableView->setColumnWidth(4,80);
    this->ui->tableView->setColumnWidth(5,80);
    this->ui->tableView->setColumnWidth(6,80);
    this->ui->tableView->setColumnWidth(7,80);
    this->ui->tableView->setColumnWidth(8,80);
}

void Widget::InitItemStokes()
{
    this->modelStokes->clear();//清除表格，每次射之前调用该函数
    //设置表头
    this->modelStokes->setHorizontalHeaderItem(0,new QStandardItem("游标:"));
    this->modelStokes->setHorizontalHeaderItem(1,new QStandardItem("X"));
    this->modelStokes->setHorizontalHeaderItem(2,new QStandardItem("Y"));

    this->ui->tableViewStokes->setModel(modelStokes);
    this->ui->tableViewStokes->setColumnWidth(0,60);
    this->ui->tableViewStokes->setColumnWidth(1,50);
    this->ui->tableViewStokes->setColumnWidth(2,50);
}

void Widget::InitItemDop()
{
    this->modelDop->clear();//清楚表格，每次射之前调用该函数
    //设置表头
    this->modelDop->setHorizontalHeaderItem(0,new QStandardItem("游标:"));
    this->modelDop->setHorizontalHeaderItem(1,new QStandardItem("X"));
    this->modelDop->setHorizontalHeaderItem(2,new QStandardItem("Y"));

    this->ui->tableViewDop->setModel(modelDop);
    this->ui->tableViewDop->setColumnWidth(0,60);
    this->ui->tableViewDop->setColumnWidth(1,50);
    this->ui->tableViewDop->setColumnWidth(2,50);

}

void Widget::btnBegin()
{
    if(flag == 0)
    {
        connect(UdpSignal.ReceT, &ReceiveThread::SendSignal, this, &Widget::Algorithm);//将最终数据送入算法处理函数
        flag = 1;
        this->ui->btnBegin->setText("暂停");
    }
    else if(flag == 1)
    {
        disconnect(UdpSignal.ReceT, &ReceiveThread::SendSignal, this, &Widget::Algorithm);//将最终数据送入算法处理函数
        flag = 2;
        this->ui->btnBegin->setText("继续");
    }
    else
    {
        connect(UdpSignal.ReceT, &ReceiveThread::SendSignal, this, &Widget::Algorithm);//将最终数据送入算法处理函数
        flag = 1;
        this->ui->btnBegin->setText("暂停");
    }
}

void Widget::btnReset()
{
    plotball.Reset();
    Sop.Reset();
    WaveStokes.Reset();
    WaveDop.Reset();
    InitItemStokes();
    InitItemDop();
    InitItemModel();
    flag_dop = 0;
    flag_stokes = 0;
    this->ui->btnBegin->setText("开始");
    this->ui->LabelS1->clear();
    this->ui->LabelS2->clear();
    this->ui->LabelS3->clear();
    this->ui->LabelAzimuth->clear();
    this->ui->LabelEllipticity->clear();
    this->ui->LabelDOP->clear();
    this->ui->LabelDOLP->clear();
    this->ui->LabelDOCP->clear();
    this->ui->LabelFER->clear();

    flag = 0;//解决没有暂停直接复位再次开始失效的bug
    disconnect(UdpSignal.ReceT, &ReceiveThread::SendSignal, this, &Widget::Algorithm);//将最终数据送入算法处理函数
}

void Widget::Algorithm(double mesage)
{
    static int num = 0;
    int i = 0;
    double s0 = 0,s1 = 0,s2 = 0,s3 = 0,DOP = 0,DOLP = 0,DOCP = 0,azimuth = 0,ellipticity = 0,temp = 0;
    QString str,str_temp;           //QString::asprintf("%.2f", 123.12545)
    double theta = 1;
//    if(num%N != 0)
//    {
//        data[num] = 0.25 * sin(2*PI*num/N) + 0.5;
//        qDebug()<< num;
//        num++;
//    }
    static int flag = 1;//模拟不用波形
    for(i = 0;i< N;i++)
    {
        switch(flag)
        {
            case 1:data[i] = 0.25 * sin(4*2*PI*i/N + PI/2) + 0.75;	//水平偏振光 + 0.05*(rand()%6/3 - 1)
            break;
            case 2:data[i] = 0.25 * sin(4*2*PI*i/N + PI) + 0.5;	   //135°偏振光
            break;
            case 3:data[i] = 0.5 * sin(2*2*PI*i/N) + 0.5;          //左圆偏振光
            break;
            case 4:data[i] = 0.5 * sin(2*2*PI*i/N + PI) + 0.5;     //右圆偏振光
            break;
        }
    }

    //模拟代码
//    flag++;
//    if(flag == 5)
//        flag = 1;


    temp =  data[i];
    str = str.sprintf("%.3f",temp);
    //temp = QString::number(temp,'f',3);
//    else
    {
        for(i = 0;i< N;i++)
        {
            //qDebug()<<data[i];
            theta = i/(N-1.0)*2*PI;
            if(i == 0 || i == N-1)
            {
                s0 = s0 + 1/PI*data[i] - 2/PI*data[i]*cos(4*theta);
                s1 = s1 + 4/PI*data[i]*cos(4*theta);
                s2 = s2 + 4/PI*data[i]*sin(4*theta);
                s3 = s3 - 2/PI*data[i]*sin(2*theta);
            }
            else
            {
                if(i%2 == 0)
                {
                    s0 = s0 + 2*(1/PI*data[i] - 2/PI*data[i]*cos(4*theta));
                    s1 = s1 + 2*(4/PI*data[i]*cos(4*theta));
                    s2 = s2 + 2*(4/PI*data[i]*sin(4*theta));
                    s3 = s3 + 2*(-2/PI*data[i]*sin(2*theta));
                }
                else
                {
                    s0 = s0 + 4*(1/PI*data[i] - 2/PI*data[i]*cos(4*theta));
                    s1 = s1 + 4*(4/PI*data[i]*cos(4*theta));
                    s2 = s2 + 4*(4/PI*data[i]*sin(4*theta));
                    s3 = s3 + 4*(-2/PI*data[i]*sin(2*theta));
                }
            }

        }
        s0 = s0/3*(2*PI/N);                                           //计算参量
        s1 = s1/3*(2*PI/N);
        s2 = s2/3*(2*PI/N);
        s3 = s3/3*(2*PI/N);
        qDebug() << s0 << s1 << s2 << s3;
        DOP = sqrt(s1*s1+s2*s2+s3*s3)/s0*100;                            //偏振度
        DOLP = sqrt(s1*s1+s2*s2)/s0*100;                                 //线偏振度
        DOCP = sqrt(s3*s3)/s0*100;                                       //椭圆偏振度
        azimuth = 1/2.0*atan(s2/s1)/(2*PI)*360;                           //azimuth方位角   ellipticity椭圆度
        if(azimuth < 0)
            azimuth = azimuth + 180;                                    //角度补偿
        if(s3/s0 > 1)                                                       //防止s3/s0超过界限(-1,1)
            temp = 1;
        else if(s3/s0 <-1)
              temp = -1;
        else
            temp = s3/s0;
        ellipticity = 1/2.0*asin(temp)/(2*PI)*360;                           //注意 只能是 1/2.0 而不能是 1/2
        setValue(s1,s2,s3,DOP,DOLP,DOCP,azimuth,ellipticity,s0);
        Sop.DataPlotSop(azimuth,ellipticity);
        plotball.randVector(s1,s2,s3);                                      //画图
        WaveStokes.DataPlotSop(s1,s2,s3);
        WaveDop.DataPlotSop(DOP,DOLP,DOCP);
        num = 0;s0 = 0;s1 = 0;s2 = 0;s3 = 0;
    }
}

void Widget::setValue(double s1,double s2,double s3,double DOP,double DOLP,double DOCP,double azimuth,double ellipticity,double power)
{
    QString str;
     str = str.sprintf("%.3f",s1);
     this->ui->LabelS1->setText(str);
     this->model->setItem(0,0,new QStandardItem(str));

     str = str.sprintf("%.3f",s2);
     this->ui->LabelS2->setText(str);
     this->model->setItem(0,1,new QStandardItem(str));

     str = str.sprintf("%.3f",s3);
     this->ui->LabelS3->setText(str);
     this->model->setItem(0,2,new QStandardItem(str));

     str = str.sprintf("%.3f",azimuth);
     this->ui->LabelAzimuth->setText(str);
     this->model->setItem(0,6,new QStandardItem(str + "°"));

     str = str.sprintf("%.3f",ellipticity);
     this->ui->LabelEllipticity->setText(str);
     this->model->setItem(0,7,new QStandardItem(str + "°"));

     str = str.sprintf("%.3f",DOP);
     this->ui->LabelDOP->setText(str + "%");
     this->model->setItem(0,3,new QStandardItem(str + "%"));

     str = str.sprintf("%.3f",DOLP);
     this->ui->LabelDOLP->setText(str + "%");
     this->model->setItem(0,4,new QStandardItem(str + "%"));

     str = str.sprintf("%.3f",DOCP);
     this->ui->LabelDOCP->setText(str + "%");
     this->model->setItem(0,5,new QStandardItem(str + "%"));

     //str = str.sprintf("%.3f",qrand()/(32767+0.0)*10);
     str = str.sprintf("%.3f",0.3);
     this->ui->LabelFER->setText(str);
     this->model->setItem(0,8,new QStandardItem(str));
     this->ui->LabelPower->setText(str.sprintf("%.3f",power));

      cnt = str.sprintf("%.3f",s1) + " ";                                   //由于str.sprintf函数限制
      cnt +=str.sprintf("%.3f",s2) + " ";                                   //如果写到一行
      cnt += str.sprintf("%.3f",s3) + " ";                                  //则保存的数字全为s1，故分为8行写
      cnt += str.sprintf("%.3f",DOP) + " ";
      cnt += str.sprintf("%.3f",DOLP) + " ";
      cnt += str.sprintf("%.3f",DOCP) + " ";
      cnt += str.sprintf("%.3f",azimuth) + " ";
      cnt += str.sprintf("%.3f",ellipticity) + " ";
      cnt += str.sprintf("%.3f",0.3)+ "\n";
}

void Widget::Init3D()
{
    //3D图初始化代码
    QHBoxLayout *hLayout = new QHBoxLayout(this->ui->widgetScatter);
    QVBoxLayout *vLayout = new QVBoxLayout();//垂直布局
    hLayout->addWidget(plotball.graphContainer, 1);//将container添加到水平布局中
    hLayout->addLayout(vLayout);
}

void Widget::InitSop()
{
    Sop.chart.axisX()->setRange(-1.05,1.05);
    Sop.chart.axisY()->setRange(-1.05,1.05);
    QChartView *chartView = new QChartView(&Sop.chart);
    QGridLayout *baseLayout = new QGridLayout(); //便于显示，创建网格布局
    //chartView->setRenderHint(QPainter::Antialiasing);
    baseLayout->addWidget(chartView, 0, 0);
    this->ui->widgetSop->setLayout(baseLayout); //显示到QWidget控件
}

void Widget::InitWaveStokes()
{
    WaveStokes.chart.axisX()->setRange(0,10);
    WaveStokes.chart.axisY()->setRange(-1,1);
    this->ui->widgetWaveStokes->setChart(&WaveStokes.chart);
    this->ui->widgetWaveStokes->setCursor(Qt::CrossCursor); //设置鼠标指针为十字星

}

void Widget::InitWaveDop()
{
    WaveDop.chart.axisX()->setRange(0,10);
    WaveDop.chart.axisY()->setRange(0,120);
    this->ui->widgetWaveDop->setChart(&WaveDop.chart);
    this->ui->widgetWaveDop->setCursor(Qt::CrossCursor); //设置鼠标指针为十字星
}

void Widget::mouseMovePointStokes(QPoint point)
{ //鼠标移动响应
    QPointF pt=ui->widgetWaveStokes->chart()->mapToValue(point); //转换为图表的数值
    ui->LabelStokes->setText(QString::asprintf("X=%.1f,Y=%.2f",pt.x(),pt.y())); //状态栏显示
}

void Widget::mouseMovePointDop(QPoint point)
{ //鼠标移动响应
    QPointF pt=ui->widgetWaveDop->chart()->mapToValue(point); //转换为图表的数值
    ui->LabelDop->setText(QString::asprintf("X=%.1f,Y=%.2f",pt.x(),pt.y())); //状态栏显示
}


void Widget::mousePressStokes(QPoint point)
{
    QPointF pt=ui->widgetWaveStokes->chart()->mapToValue(point); //转换为图表的数值
    QString str;
    this->modelStokes->setItem(flag_stokes,0,new QStandardItem(str.sprintf("%d",flag_stokes+1)));
    this->modelStokes->setItem(flag_stokes,1,new QStandardItem(str.sprintf(  "%.2f",pt.x()  )    )  );
    this->modelStokes->setItem(flag_stokes,2,new QStandardItem(str.sprintf(  "%.2f",pt.y()  )    )  );
    flag_stokes++;
}

void Widget::mousePressDop(QPoint point)
{
    QPointF pt=ui->widgetWaveDop->chart()->mapToValue(point); //转换为图表的数值
    QString str;
    this->modelDop->setItem(flag_dop,0,new QStandardItem(str.sprintf("%d",flag_dop+1)));
    this->modelDop->setItem(flag_dop,1,new QStandardItem(str.sprintf(  "%.2f",pt.x()  )    )  );
    this->modelDop->setItem(flag_dop,2,new QStandardItem(str.sprintf(  "%.2f",pt.y()  )    )  );
    flag_dop++;
}

void Widget::FunctionChoosepath()
{
    //QString file_path = QFileDialog::getExistingDirectory(this, "请选择文件路径...", "./");
    file_path = QFileDialog::getSaveFileName(this,
            tr("Open Config"),
            "",
            tr("Config Files (*.txt)"));
    if(!file_path.isEmpty())
    {
        this->ui->LineSavepath->setText(file_path);
    }
    //qDebug()<<file_path;

}

void Widget::FunctionSave()
{
    QFile file(file_path);
    if(!file.open(QIODevice::Append | QIODevice::Text))
    {
        QMessageBox::critical(this,"错误","文件打开失败，信息没有保存!","确定");
        return;
    }
    QTextStream out(&file);
    out<<cnt;          //写入
    file.close();
}
void Widget::FunctionChoosepath_Read()      //选择文件读取路径槽函数
{
    file_path = QFileDialog::getOpenFileName(this,
            tr("Open Config"),
            "",
            tr("Config Files (*.txt)"));
    if(!file_path.isEmpty())
    {
        this->ui->LineReadpath->setText(file_path);
    }
}
void Widget::FunctionRead()                //读取文件槽函数
{
    QFile file(file_path);
    if(!file.open(QIODevice::ReadOnly | QIODevice::Text))
    {
        QMessageBox::critical(this,"错误","文件打开失败!","确定");
    }

    QTextStream in(&file);

    while(!in.atEnd())
    {
        QString line = in.readLine();
        stu_lines.append(line);
    }
    file.close();

    QString line = stu_lines.at(0);
    line = line.trimmed();                                      //trimmed可以将字符串前后空白去掉；
    QStringList subs = line.split(" ");
    for(int i = 0;i<9;i++)
        this->model->setItem(0,i,new QStandardItem(subs.at(i)));
}
