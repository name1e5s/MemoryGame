#ifndef COMMON_H
#define COMMON_H

#include <QString>

const int TYPE_ADMIN = 0;
const int TYPE_GAMER = 1;

struct BaseUser {
  QString userName;
  QString realName;
  int levelPassed;
  int experience;
};

struct LoginRequest {
  int userType;
  QString userName;
  QString userPassword;
};

struct RegisterRequest {
  int userType;
  QString userName;
  QString realName;
  QString userPassword;
};

#define DEFER_1(x, y) x##y
#define DEFER_2(x, y) DEFER_1(x, y)
#define DEFER_0(x) DEFER_2(x, __COUNTER__)
#define defer(expr) auto DEFER_0(_defered_option) = deferer([&]() { expr; })

template <typename Function> struct doDefer {
  Function f;
  doDefer(Function f) : f(f) {}
  ~doDefer() { f(); }
};

template <typename Function> doDefer<Function> deferer(Function F) {
  return doDefer<Function>(F);
}

#endif
