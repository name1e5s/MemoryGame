#ifndef BASICINFO_H
#define BASICINFO_H
#include <cstdint>
#include <json.hpp>
#include <string>

namespace Basic {
using nlohmann::json;
using std::string;
using uid_t = string;  // User id.
using pass_t = string; // md5 password

struct LoginInfo {
  uid_t uid;
  pass_t pass;
};

// 1 easy
// 2 normal
// 3 hard
struct WordInfo {
  string word;
  int difficulty;
};

struct BasePerson {
  uid_t uid;
  string realName;
};

struct Gamer : public BasePerson {
  int levelPassed;
  int level;
  int exp;
  int currDifficulty;
};

struct Admin : public BasePerson {
  int level;
  int questionCount;
};
} // namespace Basic
#endif // BASICINFO_H
