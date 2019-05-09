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
  bool updateUser(const BaseUser *user);
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
