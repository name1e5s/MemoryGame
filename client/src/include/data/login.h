#ifndef LOGIN_H
#define LOGIN_H
#include <sqlite_modern_cpp.h>
#include "BasicInfo.h"

class Login {
 public:
  typedef enum {
    S_NOERROR,
    S_NXUSER,
    S_WRONGPASS,
    S_USEREXISTS,
    S_TYPERR,
    S_UNKNOWN
  } status;
  static Login& Instance();
  static void destroy();

  void insert(std::string uid,
              std::string pass,
              int isGamer,
              std::string realName = "U") {
    db << "INSERT INTO user "
          "(uid,password,real_name,level,exp,gamer,level_passed) VALUES "
          "(?,?,?,?,?,?,?);"
       << uid << pass << realName << 0 << 0 << isGamer << 0;
  }

  std::pair<status, Gamer> getGamer(std::string uid, std::string pass) {
    Gamer g;
    status test = S_NOERROR;
    int count = 0;
    db << "SELECT COUNT(*) FROM user where uid=?" << uid >> count;
    if (count != 1) {
      return std::make_pair(S_NXUSER, g);
    }
    db << "SELECT uid,password,real_name,level,exp,gamer,level_passed FROM "
          "user WHERE uid=? LIMIT 1;"
       << uid >>
        [&](std::string uid, std::string password, std::string real_name,
            int level, int exp, int gamer, int levelPassed) {
          if (password != pass)
            test = S_WRONGPASS;
          if (gamer == 0)
            test = S_TYPERR;
          g.uid = uid;
          g.level = level;
          g.exp = exp;
          g.levelPassed = levelPassed;
          g.currDifficulty = 1;
          g.realName = real_name;
        };
    return std::make_pair(test, g);
  }

  std::pair<status, Admin> getAdmin(std::string uid, std::string pass) {
    Admin g;
    status test = S_NOERROR;
    int count = 0;
    db << "SELECT COUNT(*) FROM user where uid=?" << uid >> count;
    if (count != 1) {
      return std::make_pair(S_NXUSER, g);
    }
    db << "SELECT uid,password,real_name,level,exp,gamer,level_passed FROM "
          "user WHERE uid=? LIMIT 1;"
       << uid >>
        [&](std::string uid, std::string password, std::string real_name,
            int level, int exp, int gamer, int levelPassed) {
          if (password != pass)
            test = S_WRONGPASS;
          if (gamer == 1)
            test = S_TYPERR;
          g.uid = uid;
          g.level = level;
          g.questionCount = levelPassed;
          g.realName = real_name;
        };
    return std::make_pair(test, g);
  }

  void updateUser(const Gamer& gamer) {
    db << "UPDATE user SET level=?,exp=?,level_passed=? WHERE uid=?;"
       << gamer.level << gamer.exp << gamer.levelPassed << gamer.uid;
  }

  void updateUser(const Admin& admin) {
    db << "UPDATE user SET level=?,level_passed=? WHERE uid=?;" << admin.level
       << admin.questionCount << admin.uid;
  }

 private:
  Login(const char* path = "user.db") : db(path) {
    db << "CREATE TABLE IF NOT EXISTS user ("
          "  uid TEXT primary key not null,"
          "  password TEXT not null,"
          "  real_name TEXT NOT NULL,"
          "  level INT NOT NULL,"
          "  exp INT NOT NULL,"
          "  gamer INT NOT NULL,"
          "  level_passed INT NOT NULL"
          ");";
    int count = 0;
    db << "SELECT COUNT(*) FROM user" >> count;
    if (count == 0) {
      insert("user", "test", 1);
      insert("admin", "test", 0);
    }
  }
  sqlite::database db;
  static Login* _instance;
};
#endif  // LOGIN_H
