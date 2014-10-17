/*
 * Listener.cpp
 *
 *  Created on: 2014-10-16
 *      Author: Roger
 */

#include <src/Listener.h>
#include <QSettings>
#include <QStringList>

Listener::Listener() :
    QObject(),
    m_server(new QUdpSocket(this))
{
    sendToConsoleDebug = false;

    listenOnPort(CLIENT_LISTENING_PORT);

    connect(this, SIGNAL(receivedData(QString)), this, SLOT(onReceivedData(QString)));
}

Listener::~Listener()
{
}

void Listener::listenOnPort(int _port)
{
    m_server->bind(QHostAddress::Any, _port);
    connect(m_server, SIGNAL(readyRead()), this, SLOT(onReadyRead()));
}

void Listener::onReadyRead()
{
    while (m_server->hasPendingDatagrams())
    {
        QByteArray datagram;
        datagram.resize(m_server->pendingDatagramSize());
        QHostAddress sender;
        quint16 senderPort;

        m_server->readDatagram(datagram.data(), datagram.size(),&sender, &senderPort);
        QString data = QString(datagram);

        emit receivedData(data);
    }
}

void Listener::onReceivedData(QString _data)
{
//    qDebug() << "Received this from ConsoleDebug :" << _data;
    QStringList allData = _data.split("$$");
    if (allData.size() < 3)
        return;

    QString appName = allData[0];
    QString command = allData[1].toLower();
    QString data = allData[2];

    if ((command == "consoledebugstarted") || (command == "pong")) {
        sendToConsoleDebug = true;
        QSettings settings;
        settings.setValue("sendToConsoleDebug", sendToConsoleDebug);
    }

    if (command == "consoledebugstopped") {
        sendToConsoleDebug = false;
        QSettings settings;
        settings.setValue("sendToConsoleDebug", sendToConsoleDebug);
    }
}
