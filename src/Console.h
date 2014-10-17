/*
 * Console.h
 *
 *  Created on: 2014-10-16
 *      Author: Roger
 */

#ifndef CONSOLE_H_
#define CONSOLE_H_

#include <QObject>
#include <QtNetwork/QUdpSocket>

#define CLIENT_SENDING_PORT 10465

class Console : public QObject
{
    Q_OBJECT
public:
    Console();
    virtual ~Console();

    void sendMessage(QString _command);

private:
    QUdpSocket *m_socket;
};

#endif /* Console_H_ */
