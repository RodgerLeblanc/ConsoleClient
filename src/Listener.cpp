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
    m_server->deleteLater();
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
    qDebug() << "Received this from ConsoleDebug :" << _data;
    QStringList allData = _data.split("##");
    if (allData.size() < 2)
        return;

    QString appName = allData[0];
    QString data = allData[1];

    QStringList command = data.split("&&");

    if (command.isEmpty())
        return;

    if ((command.first().toLower() == "consoledebugstarted") || (command.first().toLower() == "pong")) {
        sendToConsoleDebug = true;
        QSettings settings;
        settings.setValue("sendToConsoleDebug", sendToConsoleDebug);
    }

    if (command.first().toLower() == "consoledebugstopped") {
        sendToConsoleDebug = false;
        QSettings settings;
        settings.setValue("sendToConsoleDebug", sendToConsoleDebug);
    }

    if (command.first().toLower() == "changesettings") {
        if (command.size() >= 3) {
            QSettings settings;
            if (settings.contains(command[1])) {
                settings.setValue(command[1], command[2]);
                qDebug() << "Settings '" + command[1] + "' changed to '" + command[2] + "' successfully!";
            }
            else {
                qDebug() << "This settings doesn't exist";
            }
        }
        else {
            qDebug() << "Not enough arguments to change settings";
        }


    }
}
