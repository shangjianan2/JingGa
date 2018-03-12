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
#include <QNetworkDatagram>


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
        qDebug() << p_char;
//        qDebug() << p_char[0];
        if(p_char[0] == '0'){
            if(p_char[1] > '2'){
                green_red = 0;
//                qDebug() << "green_red = 0";
            }else{
                green_red = 1;
//                qDebug() << "green_red = 1";
            }
        }else{
            if(p_char[1] > '2'){
                green_red = 2;
//                qDebug() << "green_red = 2";
            }else{
                green_red = 3;
//                qDebug() << "green_red = 3";
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
    const QByteArray constByteArray = sendmessage.toLatin1();
    const char* constData = (const char*)constByteArray.constData();
    qDebug() << constData;
    qus_tt.writeDatagram(&constData[0], constByteArray.length(), QHostAddress(address), port.toUInt());
    //qus_tt.writeDatagram(&constData[1], QHostAddress(address), 2333);
    //const char* constData = (const char *)data.constData();
    //qus_tt.wri
}

void UdpReceiver::sendto2(QString sendmessage, QString address, QString port, QString my_address, QString my_port)
{
//    QUdpSocket qus_tt;
//    const QByteArray constByteArray = sendmessage.toLatin1();
//    const char* constData = (const char*)constByteArray.constData();
//    qDebug() << constData;
//    qus_tt.writeDatagram(&constData[0], constByteArray.length(), QHostAddress(address), port.toUInt());

    QUdpSocket qus_tt;
    const QByteArray constByteArray = sendmessage.toLatin1();
    QNetworkDatagram network_tt;// = QNetworkDatagram::QNetworkDatagram(constByteArray, QHostAddress(address), port.toUInt());
    network_tt.setData(constByteArray);
    network_tt.setDestination(QHostAddress(address), port.toUInt());
    network_tt.setSender(QHostAddress(my_address), my_port.toUInt());
    qus_tt.writeDatagram(network_tt);
}
