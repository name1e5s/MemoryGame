#ifndef LOGIN_H
#define LOGIN_H
#include <QString>
#include <QtSql>
#include <stdexcept>
#include "BasicInfo.h"

class Login {
 public:
  static Login& Instance();
  static void destroy();

  void insert(QString uid, QString pass, int isGamer, QString realName) {
    QSqlQuery qry;
    QString str =
        "INSERT INTO user "
        "(uid,password,real_name,level,exp,gamer,level_passed) VALUES "
        "('%1','%2','%3',%4,%5,%6,%7);";
    qry.prepare(
        str.arg(uid).arg(pass).arg(realName).arg(0).arg(0).arg(isGamer).arg(0));
    if (!qry.exec()) {
      throw qry.lastError();
    }
  }

  Gamer getGamer(QString uid, QString pass) {
    Gamer g;
    QString str =
        "SELECT uid,password,real_name,level,exp,gamer,level_passed FROM user "
        "WHERE uid='%1' AND password='%2' LIMIT 1;";
    QSqlQuery qry;
    qry.prepare(str.arg(uid).arg(pass));
    if (qry.exec()) {
      if (qry.next() && qry.value(5).toInt() == 1) {
        g.uid = qry.value(0).toString().toStdString();
        g.realName = qry.value(2).toString().toStdString();
        g.level = qry.value(3).toInt();
        g.exp = qry.value(4).toInt();
        g.levelPassed = qry.value(6).toInt();
        g.currDifficulty = 1;
        return g;
      }
    }
    throw std::runtime_error("");
  }

  Admin getAdmin(QString uid, QString pass) {
    Admin g;
    QString str =
        "SELECT uid,password,real_name,level,exp,gamer,level_passed FROM user "
        "WHERE uid='%1' and password='%2' LIMIT 1;";
    QSqlQuery qry;
    qry.prepare(str.arg(uid).arg(pass));
    if (!qry.exec()) {
      if (qry.next() && qry.value(5).toInt() == 1) {
        g.uid = qry.value(0).toString().toStdString();
        g.realName = qry.value(2).toString().toStdString();
        g.level = qry.value(3).toInt();
        g.questionCount = qry.value(4).toInt();
        return g;
      }
    }
    throw std::runtime_error("");
  }

  void updateUser(const Gamer& gamer) {
    QString str =
        "UPDATE user SET level=%1,exp=%2,level_passed=%3 WHERE uid='%4';";
    QSqlQuery qry;
    qry.prepare(str.arg(gamer.level)
                    .arg(gamer.exp)
                    .arg(gamer.levelPassed)
                    .arg(QString::fromStdString(gamer.uid)));
    qry.exec();
  }

  void updateUser(const Admin& admin) {
    QString str = "UPDATE user SET level=%1,level_passed=%2 WHERE uid='%3';";
    QSqlQuery qry;
    qry.prepare(str.arg(admin.level)
                    .arg(admin.questionCount)
                    .arg(QString::fromStdString(admin.uid)));
    qry.exec();
  }

 private:
  Login(const char* path = "./user.db") {
    db = QSqlDatabase::addDatabase("QSQLITE");
    db.setDatabaseName(path);
    if (!db.open()) {
      qDebug() << db.lastError();
    }
    QSqlQuery qry;
    qry.prepare(
        "CREATE TABLE IF NOT EXISTS user ("
        "  uid TEXT primary key not null,"
        "  password TEXT not null,"
        "  real_name TEXT NOT NULL,"
        "  level INT NOT NULL,"
        "  exp INT NOT NULL,"
        "  gamer INT NOT NULL,"
        "  level_passed INT NOT NULL"
        ");");
    qry.exec();
    int count = 0;
    qry.prepare("SELECT COUNT(*) FROM user");
    qry.exec();
    if (qry.next()) {
      count = qry.value(0).toInt();
    }
    if (count == 0) {
      insert("user", "test", 1, "user");
      insert("admin", "test", 0, "admin");
    }
  }
  QSqlDatabase db;
  static Login* _instance;
};
#endif  // LOGIN_H
