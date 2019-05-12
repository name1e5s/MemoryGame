#include <QDebug>
#include <common.h>
#include <request_handler.h>
#include <socket_client.h>
#include <socket_server.h>
#include <uid.h>
#include <vector>

using std::vector;
vector<SocketClient *> RequestHandler::clients;

using namespace RequestHandler;

void broadCast(std::string key, std::string message, SocketClient *exception) {
  uint32_t _uid = exception->getTag();
  for (auto x : clients) {
    uint32_t uid = x->getTag();
    if ((uid) != (_uid)) {
      x->send(key, message);
    }
  }
}

static void onDisconnect(SocketClient *socket) {
  qDebug() << "client disconnected !";
  broadCast("message", {"Client disconnected"}, socket);
  uint32_t _uid = socket->getTag();
  for (unsigned int i = 0; i < clients.size(); i++) {
    uint32_t uid = clients[i]->getTag();
    if ((uid) != (_uid)) {
      clients.erase(clients.begin() + i);
    }
  }
  delete socket;
}

void RequestHandler::initilizeClient(SocketClient *client) {
  client->setDisconnectListener(onDisconnect);
}
