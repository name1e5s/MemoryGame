#ifndef SOCKET_CLIENT_H
#define SOCKET_CLIENT_H

#include <arpa/inet.h>
#include <functional>
#include <map>
#include <string>
#include <sys/socket.h>
#include <thread>
#include <unistd.h>
#include <vector>

struct DataInterface {
  std::function<void(void *)> mDestroy;

  DataInterface() {}

  DataInterface(std::function<void(void *)> destroy) { mDestroy = destroy; }
};

class SocketClient {
public:
  SocketClient();
  SocketClient(std::string address, int port);
  SocketClient(int socket);
  ~SocketClient();

  int getSocket();
  void *getTag();

  bool connect();
  void disconnect();
  bool send(std::string key, std::vector<std::string> messages);
  bool send(std::string key, std::string message);
  void addListener(std::string key,
                   void (*messageListener)(SocketClient *, std::string));
  void setDisconnectListener(void (*disconnectListener)(SocketClient *));
  void setTag(void *tag, DataInterface interface);

private:
  void *m_tag;
  DataInterface m_dataInterface;

  struct sockaddr_in m_server;
  std::string m_address;
  int m_port;
  int m_socket;
  bool m_connected;
  bool m_threadStopped;

  int m_packetSize;

  std::map<std::string, void (*)(SocketClient *, std::string)>
      m_messageListenerMap;
  void (*m_disconnectListener)(SocketClient *);

  void receiveThread();
  static void staticReceiveThread(SocketClient *client) {
    client->receiveThread();
  }
  int receive(std::string &message);
  bool send(std::string message);
};

#endif // SOCKET_CLIENT_H
