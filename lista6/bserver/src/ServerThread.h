#ifndef SERVERTHREAD_H
#define SERVERTHREAD_H

#include <QtCore/QThread>
#include <QtNetwork/QTcpSocket>

class ServerThread : public QThread
{
	Q_OBJECT

public:
	ServerThread(qintptr socketDescriptor, QObject *parent);
	void run() override;

signals:
	void error(QTcpSocket::SocketError socketError);

protected:
	QString blockingReadLine(QTcpSocket &socket);
private:
	qintptr socketDescriptor;
};

#endif
