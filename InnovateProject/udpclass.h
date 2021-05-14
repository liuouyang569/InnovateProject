#ifndef UDPCLASS_H
#define UDPCLASS_H

#include <QWidget>
#include <QUdpSocket>
#include <QThread>
#include <QHostAddress>
#include "receivethread.h"

class UDPclass : public QWidget
{
    Q_OBJECT
public:
    QUdpSocket *UdpSocket;
    ReceiveThread *ReceT;
    QThread *thread;

    QHostAddress cliAddr;//远端IP地址
    quint16 port;//远端端口号
    char ReceBuf[1024]={0};//定义缓冲区,1024为一次最多可以接收的字节

    int RomBuf[1024] = {0};//储存每一次的数据
    explicit UDPclass(QWidget *parent = nullptr);
    ~UDPclass();

    void SendMessage();//槽函数，发送数据
    void ClearContext();//槽函数，清除接收到的数据
    void DisplayMessage(double Message);//槽函数，显示数据
    void ReceiveMessage();//接收UDP数据的槽函数
    void dealClose();//窗口关闭槽函数

    void ClearBufferData();//缓存清除槽函数
signals:
    void ReceDeal(char *bufMessage);//接收处理信号

public slots:




};

#endif // UDPCLASS_H
