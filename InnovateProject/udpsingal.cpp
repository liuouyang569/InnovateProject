#include "udpsingal.h"

UdpSingal::UdpSingal()
{
    //自定义对象,不能指定父对象
    ReceT = new ReceiveThread;
    //创建子线程
    //thread = new QThread(this);
    //将自定义的模块添加到子线程中
    ReceT->moveToThread(thread);
    //启动子线程
    thread->start();

    //分配空间，指定父对象
    //UdpSocket = new QUdpSocket(this);

    UdpSocket->bind(8089);//绑定端口8089
}
