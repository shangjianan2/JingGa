#ifndef UDPRECEIVER_H
#define UDPRECEIVER_H

#include <QObject>
#include <QUdpSocket>

class UdpReceiver : public QObject
{
    Q_OBJECT

public:
    UdpReceiver(QObject *p = 0);
    ~UdpReceiver();

public slots:
    void receive();
    bool return_gr();

private:
    QUdpSocket *uSocket;

    //from lunge
public:
    bool green_red;

signals:
    void senddate(char *data);
};

#endif // UDPRECEIVER_H
