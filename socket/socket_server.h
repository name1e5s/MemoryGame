#ifndef SOCKET_H
#define SOCKET_H

#include <arpa/inet.h>
#include <sys/socket.h>

class SocketServer {
public:
  SocketServer(int port = 8888);
  bool start();
  int accept();

private:
  int m_port;
  int m_socket;
  struct sockaddr_in m_server;
};

#endif // SOCKET_H
