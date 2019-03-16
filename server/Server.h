#ifndef SERVER_H
#define SERVER_H

#include <BasicInfo.h>
#include <bits/stdc++.h>
#include <functional>

using std::string;
namespace Server {

class Server {
public:
  Server();

private:
  std::unordered_map<
      std::string, std::function<void(const string &request, string &response)>>
      _handler_table;
  std::unordered_map<uint64_t, GameInfo::Gamer> _gamer_table;
  std::unordered_map<uint64_t, GameInfo::Admin> _admin_table;
};
} // namespace Server

#endif // SERVER_H
