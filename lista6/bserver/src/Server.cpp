#include "Server.h"

#include "ServerThread.h"

void Server::incomingConnection(qintptr socketDescriptor)
{
  ServerThread *thread = new ServerThread(socketDescriptor, this);
  connect(thread, &ServerThread::finished, thread, &ServerThread::deleteLater);
  thread->start();
}
