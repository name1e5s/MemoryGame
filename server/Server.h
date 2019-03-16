#ifndef SERVER_H
#define SERVER_H

#include <BasicInfo.h>
#include <bits/stdc++.h>
#include <functional>

/**
 * Server module of the fucking word game.
 *
 * Request format:
 * `{"req":<request string>, "para":<some parameters>}`
 *
 * Response format:
 * `{"status": <true or false>, "response":<some data>}`
 */
using std::string;
namespace Server {

class Server {
public:
    Server() = default;

private:
  std::unordered_map<
      std::string, std::function<void(const string &request, string &response)>>
      _handler_table;
  std::unordered_map<uint64_t, Basic::Gamer> _gamer_table;
  std::unordered_map<uint64_t, Basic::Admin> _admin_table;
};
} // namespace Server

#endif // SERVER_H
