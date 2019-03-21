#ifndef BASICINFO_H
#define BASICINFO_H
#include <cstdint>
#include <string>

#include <QVariant>

using std::string;
struct LoginInfo {
  string uid;
  string pass;
};

// 1 easy
// 2 normal
// 3 hard
struct WordInfo {
  string word;
  int difficulty;
};

struct BasePerson {
  string uid;
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

Q_DECLARE_METATYPE(Gamer)
Q_DECLARE_METATYPE(Admin)

#endif  // BASICINFO_H
