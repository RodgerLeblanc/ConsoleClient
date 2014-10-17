/*
 * Listener.h
 *
 *  Created on: 2014-10-16
 *      Author: Roger
 */

#ifndef LISTENER_H_
#define LISTENER_H_

#include <QObject>
#include <bb/data/JsonDataAccess>
#include <QtNetwork/QUdpSocket>

#define CLIENT_LISTENING_PORT 10466

class Listener : public QObject
{
    Q_OBJECT
public:
    Listener();
    virtual ~Listener();

private:
    void listenOnPort(int _port);

    QUdpSocket *m_server;

    bb::data::JsonDataAccess jda;
    bool sendToConsoleDebug;

signals:
    void receivedData(QString);

public slots:
    void onReadyRead();

private slots:
    void onReceivedData(QString _data);
};

#endif /* LISTENER_H_ */
