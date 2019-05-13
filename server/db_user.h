#ifndef DB_USER
#define DB_USER
#include <QtSql>
#include <common.h>

class UserDB {
public:
  static UserDB &Instance();
  ~UserDB();

  bool registerUser(const RegisterRequest &info);
  BaseUser loginUser(const LoginRequest &info);
  void logoutUser(QString userName);
  bool updateUser(const BaseUser *user);
  bool updateUser(QString userName, int levelPassed, int experience);
  void getAdmins(QVector<QVector<QString>> &model);
  void getGamers(QVector<QVector<QString>> &model);
  int getGamersCount();
  int getAdminsCount();
  void searchAdmins(QVector<QVector<QString>> &model, QString query);
  void searchGamers(QVector<QVector<QString>> &model, QString query);

private:
  UserDB(const char *path = "./user.db");
  QSqlDatabase db;
  static UserDB *_instance;
};

#endif
