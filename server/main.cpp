#include <QCoreApplication>
#include <QDebug>
#include <bits/stdc++.h>
#include <common.h>
#include <request_handler.h>
#include <socket_client.h>
#include <socket_server.h>
#include <uid.h>

int main(int argc, char *argv[]) {
  SocketServer server(8888);
  if (server.start()) {
    qDebug() << "Got cha!";
    while (1) {
      int sock = server.accept();
      if (sock != -1) {
        qDebug() << "client connected !";
        uint32_t uid = generate_uid();
        SocketClient *client = new SocketClient(sock);
        client->setTag(uid);
        client->send("uid", std::to_string(uid));
        RequestHandler::clients.push_back(client);
      }
    }
  }
  defer(for (auto x : RequestHandler::clients) delete x;);
  return 0;
}
