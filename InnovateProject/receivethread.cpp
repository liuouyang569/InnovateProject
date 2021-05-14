#include "receivethread.h"
#include <QHostAddress>
#include <QDebug>

ReceiveThread::ReceiveThread(QObject *parent) : QObject(parent)
{

}
//在线程中处理接收到的数据
void ReceiveThread::dealMessage(char *bufMessage)
{
   char *str = bufMessage;
   int Num = 0;
   double Final_data = 0;
   static int DealBufNum = 0;
   //static int i = 0;//记录接受次数
   Num = str2int(str);//字符转化为整型

   DealBuf[DealBufNum] = Num;
//   qDebug() << "缓存" << DealBuf[DealBufNum];
   DealBufNum++;

   if(DealBufNum >= DEAL_BUF_MAX)//采集三次求均值
   {
       DealBufNum = 0;
       for(int i = 0; i < DEAL_BUF_MAX; i++)
       {
            Final_data = Final_data + DealBuf[i];
            //qDebug() << "Final_data" << Final_data;
       }
       Final_data = Final_data / DEAL_BUF_MAX;
       //qDebug() << "最终信号" << Final_data;
       //emit SendSignal(Final_data);//发送信号进行显示数据
       emit SendSignal(Final_data);//发送信号进行显示数据

       //i++;
       //qDebug()<<i;
   }
   emit DealFinished();//数据处理完毕，发送信号清除接收缓存
}
//字符转换为整型
int ReceiveThread::str2int(char *s)
{
    char *rear = s;
    int Number = 0,num = 0;
    while(*rear != '\0')
    {
        num = *rear - '0';
        Number = Number*10 + num;
        rear++;
    }
//    qDebug() << "信号" << Number;
    return Number;
}
