#ifndef RECEIVETHREAD_H
#define RECEIVETHREAD_H

#include <QObject>
#include <QUdpSocket>

#define DEAL_BUF_MAX 1

class ReceiveThread : public QObject
{
    Q_OBJECT
public:
    explicit ReceiveThread(QObject *parent = nullptr);

    void dealMessage(char *bufMessage);//槽函数，处理接收到的数据

    int str2int(char *s);

signals:
    void SendSignal(double Message);
    void DealFinished();

public slots:

private:
    int DealBuf[DEAL_BUF_MAX] = {0};
};

#endif // RECEIVETHREAD_H
