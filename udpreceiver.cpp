#include <QByteArray>
#include <iostream>
#include "udpreceiver.h"
#include <QUdpSocket>

#include <QApplication>

#include <QByteArray>
#include <QCoreApplication>
#include <QHostAddress>
#include <QUdpSocket>

#include <iostream>


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
//        qDebug() << p_char;
//        qDebug() << p_char[0];
        if(p_char[0] == '0'){
            if(p_char[1] > '2'){
                green_red = 0;
                qDebug() << "green_red = 0";
            }else{
                green_red = 1;
                qDebug() << "green_red = 1";
            }
        }else{
            if(p_char[1] > '2'){
                green_red = 2;
                qDebug() << "green_red = 2";
            }else{
                green_red = 3;
                qDebug() << "green_red = 3";
            }
        }
        emit senddate(p_char);
    }
}

int UdpReceiver::return_gr()
{
    return green_red;
}

void UdpReceiver::sendto(QString sendmessage, QString address, QString port)
{
    QUdpSocket qus_tt;
    qDebug() << sendmessage + " " + address + " " + port;
    //qus_tt.writeDatagram("sendmessage", QHostAddress(address), port);
    //qus_tt.wri
    //qus_tt.wri
}
