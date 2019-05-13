#include <QCoreApplication>
#include <QDebug>
#include <bits/stdc++.h>
#include <common.h>
#include <request_handler.h>
#include <signal.h>
#include <socket_client.h>
#include <socket_server.h>
#include <uid.h>
#include <unistd.h>

int main(void) {
  SocketServer server(8888);
  if (server.start()) {
    qDebug() << "Got cha!";
    while (1) {
      int sock = server.accept();
      if (sock != -1) {
        uint32_t uid = generate_uid();
        SocketClient *client = new SocketClient(sock);
        RequestHandler::initilizeClient(client);
        client->setTag(uid);
        client->send("uid", std::to_string(uid));
        RequestHandler::clients.push_back(client);
        qDebug() << "Client" << uid << " connected !";
      }
    }
  }
  defer(for (auto x : RequestHandler::clients) delete x;);
  return 0;
}
