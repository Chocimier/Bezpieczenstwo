#ifndef SERVER_H
#define SERVER_H

#include <QtNetwork/QTcpServer>

class Server : public QTcpServer
{
	Q_OBJECT

public:
	using QTcpServer::QTcpServer;

protected:
	void incomingConnection(qintptr socketDescriptor) override;
};

#endif
