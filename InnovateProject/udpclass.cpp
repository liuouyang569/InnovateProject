#include "udpclass.h"
#include <QString>

UDPclass::UDPclass(QWidget *parent) : QWidget(parent)
{
    //自定义对象,不能指定父对象
    ReceT = new ReceiveThread;
    //创建子线程
    thread = new QThread(this);
    //将自定义的模块添加到子线程中
    ReceT->moveToThread(thread);
    //启动子线程
    thread->start();

    //分配空间，指定父对象
    UdpSocket = new QUdpSocket(this);

    UdpSocket->bind(8089);//绑定端口8089

    setWindowTitle("服务器端口为:8089");

    /* 当对方数据成功发送过来
     * 自动触发readyRead
     * 将UdpSocket调用的readyRead处理后的数据发送给this指向的dealMessage函数
     */
    connect(UdpSocket, &QUdpSocket::readyRead, this, &UDPclass::ReceiveMessage);
    connect(this, &UDPclass::ReceDeal, ReceT, &ReceiveThread::dealMessage);
    //按键事件的信号链接
//    connect(ui->ButtonSend, &QPushButton::pressed, this, &UDPclass::SendMessage);
//    connect(ui->ButtonClose, &QPushButton::pressed, this, &UDPclass::ClearContext);
    //接收线程的信号链接
    connect(ReceT, &ReceiveThread::SendSignal, this, &UDPclass::DisplayMessage);
    //关闭窗口时的信号链接
    connect(this, &UDPclass::destroyed, this, &UDPclass::dealClose);
    //线程数据处理完的信号链接
    connect(ReceT, &ReceiveThread::DealFinished, this, &UDPclass::ClearBufferData);
}

UDPclass::~UDPclass()
{
    //delete ui;
}
void UDPclass::dealClose()
{
    //退出子线程，并回收资源
    thread->quit();
    thread->wait();
    delete ReceT;
}
//发送数据的按键槽函数
void UDPclass::SendMessage()
{
    //获取对方的IP和端口
    QString ip = QString("192.168.0.103");//ui->lineEditIP->text();
    qint16 port = 8080;//ui->lineEditPort->text().toInt();

    QString str = QString("1111");//ui->textEdit->toPlainText();//获取需要发送的内容

    UdpSocket->writeDatagram(str.toUtf8(),QHostAddress(ip),port);//发送数据
}
//清除显示的按键槽函数
void UDPclass::ClearContext()
{
    //ui->textEdit->clear();
}
//显示处理后的信息的槽函数
void UDPclass::DisplayMessage(double Message)
{
    QString str = QString("[%1;%2] %3 %4").arg(cliAddr.toString()).arg(port).arg(Message).arg('\n');
    //qDebug() << "接收到的数据" << str;
    //ui->textEdit->insertPlainText(str);
}
//接收UDP消息的槽函数
void UDPclass::ReceiveMessage()
{
    //读取对方发送的内容
    qint64 len = UdpSocket->readDatagram(ReceBuf, sizeof(ReceBuf), &cliAddr, &port);//接收到数据的长度
    if(len > 0)//接收到数据
    {
        //qDebug() << "接收到的数据长度" << len;
        SendMessage();
        emit ReceDeal(ReceBuf); //发送接收到消息的信号
    }
}
//缓存清除函数
void UDPclass::ClearBufferData()
{
    char *p = ReceBuf;
    while(*p != '\0')
    {
        *(p++) = '\0';
    }
}
