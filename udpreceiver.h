#ifndef UDPRECEIVER_H
#define UDPRECEIVER_H

#include <QObject>
#include <QUdpSocket>
#include <QNetworkDatagram>

class UdpReceiver : public QObject
{
    Q_OBJECT

public:
    UdpReceiver(QObject *p = 0);
    ~UdpReceiver();

public slots:
    void receive();
    int return_gr();
    void sendto(QString sendmessage, QString address, QString port);//发送数据;
    void sendto2(QString sendmessage, QString address, QString port, QString my_address, QString my_port);//发送数据;

private:
    QUdpSocket *uSocket;

    //from lunge
public:
    int green_red;
    //Q_INVOKABLE void sendto(QString sendmessage, QString address, QString port);//发送数据;

signals:
    void senddate(char *data);

};

#endif // UDPRECEIVER_H
