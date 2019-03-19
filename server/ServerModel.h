#ifndef SERVERVIEW_H
#define SERVERVIEW_H

#include <BasicInfo.h>
#include <bits/stdc++.h>
#include <handy/handy.h>
namespace Server {
using std::string;

class ServerModel {
public:
  ServerModel(handy::TcpConnPtr conn) : client(conn) {}

protected:
  handy::TcpConnPtr client;
};

class GamerServerModel : ServerModel {
  using ServerModel::ServerModel;

public:
  void setGamer(Basic::Gamer &&g) { gamer = std::move(g); }
  void setWord(Basic::WordInfo &&info) { word = std::move(info); }
  void right(double factor);
  void wrong(double factor);
  void setWordInfo(Basic::WordInfo &&word);

private:
  Basic::Gamer gamer;
  Basic::WordInfo word = Basic::WordInfo{"", 1};
};

class AdminServerModel : public ServerModel {
  using ServerModel::ServerModel;

public:
  void addedWord();

private:
  Basic::Admin admin;
};
} // namespace Server

#endif // SERVERVIEW_H
