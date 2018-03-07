#include <QByteArray>
#include <iostream>
#include "udpreceiver.h"

const quint16 PORT = 2333;

UdpReceiver::UdpReceiver(QObject *p) :
    QObject(p)
{
    uSocket = new QUdpSocket;
    //uSocket->bind(QHostAddress("127.0.0.1"), PORT);
    uSocket->bind(QHostAddress("192.168.170.130"), PORT);
    connect(uSocket, SIGNAL(readyRead()), this, SLOT(receive()));
}

UdpReceiver::~UdpReceiver()
{
    delete uSocket;
}

void UdpReceiver::receive()
{
    QByteArray ba;
    qDebug() << "receive OK";
    while(uSocket->hasPendingDatagrams())
    {
        ba.resize(uSocket->pendingDatagramSize());
        uSocket->readDatagram(ba.data(), ba.size());
//        if(strcmp(ba.data(), "Hello world!") == 0){
//            green_red = true;
//        }else{
//            green_red = false;
//        }
        char *p_char = ba.data();
        qDebug() << (int)(*p_char);
        if((int)(*p_char) > 2){
            green_red = true;
        }else{
            green_red = false;
        }
        emit senddate(p_char);
    }
}

bool UdpReceiver::return_gr()
{
    return green_red;
}
