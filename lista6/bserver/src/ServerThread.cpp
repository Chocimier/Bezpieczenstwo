#include "ServerThread.h"

#include <iostream>

#include <QtNetwork/QTcpSocket>

#include "bserver.h"

ServerThread::ServerThread(qintptr descriptor, QObject *parent) :
	QThread(parent),
	socketDescriptor(descriptor)
{
}

void ServerThread::run()
{
	QTcpSocket tcpSocket;
	if (!tcpSocket.setSocketDescriptor(socketDescriptor))
	{
		std::cerr << "gniazdko nie działa" << std::endl;
		emit error(tcpSocket.error());
		return;
	}
	std::string password = blockingReadLine(tcpSocket).toStdString();
	if (password_matches(password))
	{
		tcpSocket.write((QString::fromStdString("poprawne hasło\n")).toUtf8());
		do
		{
			std::string line = blockingReadLine(tcpSocket).toStdString();
			std::istringstream input(line);
			Bigint x;
			input >> x;
			auto signature = sign(x);
			if (signature.first)
			{
				tcpSocket.write(QString::fromStdString(signature.second.str() + "\n").toUtf8());
			}
			else
			{
				tcpSocket.write((QString::fromStdString("ERR " + x.str() + " nie należy do Z_n\n")).toUtf8());
			}
		} while (tcpSocket.atEnd());
	}
	else
	{
		tcpSocket.write((QString::fromStdString("ERR niepoprawne hasło\n")).toUtf8());
	}
	tcpSocket.disconnectFromHost();
	tcpSocket.waitForDisconnected();
}

QString ServerThread::blockingReadLine(QTcpSocket &socket)
{
	while (!socket.canReadLine())
	{
		socket.waitForReadyRead(2000);
	}
	QString line = socket.readLine();
	line.chop(1);
	if (line.right(1) == "\r")
	{
		line.chop(1);
	}
	return line;
}
