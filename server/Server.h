#ifndef SERVER_H
#define SERVER_H

#include <BasicInfo.h>
#include <bits/stdc++.h>
#include <functional>
#include <handy/handy.h>

// Server module of the fucking word game.

//  Request format:
//  0  1  2  3  4  5  6  7  8  9  10 11 12 13 14 15
//  +--+--+--+--+--+--+--+--+--+--+--+--+--+--+--+--+
//  |                  OPCODE                       |
//  +--+--+--+--+--+--+--+--+--+--+--+--+--+--+--+--+
//  |                      ID                       |
//  +--+--+--+--+--+--+--+--+--+--+--+--+--+--+--+--+
//  |                REQUEST STRUCT                 |
//  +--+--+--+--+--+--+--+--+--+--+--+--+--+--+--+--+

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
