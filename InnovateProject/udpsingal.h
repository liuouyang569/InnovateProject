#ifndef UDPSINGAL_H
#define UDPSINGAL_H

#include <QUdpSocket>
#include <QThread>
#include <QHostAddress>
#include "receivethread.h"

class UdpSingal
{
public:
    UdpSingal();
    //UDP所需
        QUdpSocket *UdpSocket;
        ReceiveThread *ReceT;
        QThread *thread;

        QHostAddress cliAddr;//远端IP地址
        quint16 port;//远端端口号
        char ReceBuf[1024]={0};//定义缓冲区,1024为一次最多可以接收的字节

        int RomBuf[1024] = {0};//储存每一次的数据
};

#endif // UDPSINGAL_H
