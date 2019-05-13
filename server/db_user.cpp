#include <QSet>
#include <common.h>
#include <db_user.h>

QSet<QString> userSet;

UserDB *UserDB::_instance = 0;

UserDB &UserDB::Instance() {
  if (_instance == 0)
    _instance = new UserDB;
  return *_instance;
}

UserDB::~UserDB() { db.close(); }

UserDB::UserDB(const char *path) {
  if (QSqlDatabase::contains("qt_sql_default_connection"))
    db = QSqlDatabase::database("qt_sql_default_connection");
  else
    db = QSqlDatabase::addDatabase("QSQLITE");
  db.setDatabaseName(path);
  if (!db.open()) {
    qDebug() << db.lastError();
  }

  QSqlQuery qry;
  qry.prepare("CREATE TABLE IF NOT EXISTS user ("
              "utype INT NOT NULL,"
              "uname TEXT PRIMARY KEY NOT NULL,"
              "rname TEXT NOT NULL,"
              "level INT NOT NULL,"
              "exp INT NOT NULL,"
              "password TEXT NOT NULL"
              ");");
  if (!qry.exec()) {
    qDebug() << QString::fromStdString(
        qry.lastError().driverText().toStdString());
    qDebug() << qry.executedQuery();
  }

  int count = 0;
  qry.prepare("SELECT COUNT(*) FROM user");
  qry.exec();
  if (qry.next()) {
    count = qry.value(0).toInt();
  }
  if (count == 0) {
    registerUser({TYPE_ADMIN, "admin", "admin", "password"});
    registerUser({TYPE_GAMER, "user", "user", "password"});
  }
}

bool UserDB::registerUser(const RegisterRequest &info) {
  QSqlQuery qry;
  QString qryStr = "INSERT INTO user "
                   "(utype, uname, rname, level, exp, password) VALUES "
                   "(%1, '%2', '%3', %4, %5, '%6')";
  qry.prepare(qryStr.arg(info.userType)
                  .arg(info.userName)
                  .arg(info.realName)
                  .arg(0)
                  .arg(0)
                  .arg(info.userPassword));
  if (!qry.exec()) {
    qDebug() << qry.executedQuery();
    return false;
  }
  return true;
}

BaseUser UserDB::loginUser(const LoginRequest &info) {
  QSqlQuery qry;
  BaseUser user;
  QString qryStr =
      "SELECT uname, rname, level, exp FROM user "
      "WHERE uname = '%1' AND password = '%2' AND utype = %3 LIMIT 1";
  qry.prepare(
      qryStr.arg(info.userName).arg(info.userPassword).arg(info.userType));
  if (qry.exec() && qry.next() && !userSet.contains(info.userName)) {
    user.userName = qry.value(0).toString();
    user.realName = qry.value(1).toString();
    user.levelPassed = qry.value(2).toInt();
    user.experience = qry.value(3).toInt();
    userSet.insert(info.userName);
  } else {
    user.experience = -1;
  }
  return user;
}

void UserDB::logoutUser(QString userName) {
  if (userSet.contains(userName))
    userSet.remove(userName);
}

bool UserDB::updateUser(const BaseUser *user) {
  QSqlQuery qry;
  QString qryStr = "UPDATE user SET level=%1,exp=%2 WHERE uname='%4';";
  qry.prepare(
      qryStr.arg(user->levelPassed).arg(user->experience).arg(user->userName));
  return qry.exec();
}

bool UserDB::updateUser(QString userName, int levelPassed, int experience) {
  QSqlQuery qry;
  QString qryStr = "UPDATE user SET level=%1,exp=%2 WHERE uname='%4';";
  qry.prepare(qryStr.arg(levelPassed).arg(experience).arg(userName));
  return qry.exec();
}

void UserDB::getGamers(QVector<QVector<QString>> &model) {
  QSqlQuery qry;
  QString qryStr = "SELECT uname,rname,exp,level FROM user WHERE "
                   "utype=1 ORDER BY exp DESC";
  qry.prepare(qryStr);
  if (qry.exec()) {
    while (qry.next()) {
      QVector<QString> tmp;
      tmp.push_back(qry.value(0).toString());
      tmp.push_back(qry.value(1).toString());
      tmp.push_back(qry.value(2).toString());
      tmp.push_back(qry.value(3).toString());
      tmp.push_back(userSet.contains(qry.value(0).toString()) ? "Online"
                                                              : "Offline");
      model.push_back(tmp);
    }
  }
}

void UserDB::searchGamers(QVector<QVector<QString>> &model, QString query) {
  QString qryStr =
      "SELECT uname,rname,exp,level FROM user WHERE utype=1 AND %1";
  QSqlQuery qry;
  qry.prepare(qryStr.arg(query));
  if (qry.exec()) {
    while (qry.next()) {
      QVector<QString> tmp;
      tmp.push_back(qry.value(0).toString());
      tmp.push_back(qry.value(1).toString());
      tmp.push_back(qry.value(2).toString());
      tmp.push_back(qry.value(3).toString());
      tmp.push_back(userSet.contains(qry.value(0).toString()) ? "Online"
                                                              : "Offline");
      model.push_back(tmp);
    }
  }
}

void UserDB::getAdmins(QVector<QVector<QString>> &model) {
  QSqlQuery qry;
  QString qryStr = "SELECT uname,rname,exp,level FROM user WHERE "
                   "utype=0 ORDER BY exp DESC";
  qry.prepare(qryStr);
  if (qry.exec()) {
    while (qry.next()) {
      QVector<QString> tmp;
      tmp.push_back(qry.value(0).toString());
      tmp.push_back(qry.value(1).toString());
      tmp.push_back(qry.value(2).toString());
      tmp.push_back(qry.value(3).toString());
      tmp.push_back(userSet.contains(qry.value(0).toString()) ? "Online"
                                                              : "Offline");
      model.push_back(tmp);
    }
  }
}

void UserDB::searchAdmins(QVector<QVector<QString>> &model, QString query) {
  QString qryStr =
      "SELECT uname,rname,exp,level FROM user WHERE utype=0 AND %1";
  QSqlQuery qry;
  qry.prepare(qryStr.arg(query));
  if (qry.exec()) {
    while (qry.next()) {
      QVector<QString> tmp;
      tmp.push_back(qry.value(0).toString());
      tmp.push_back(qry.value(1).toString());
      tmp.push_back(qry.value(2).toString());
      tmp.push_back(qry.value(3).toString());
      tmp.push_back(userSet.contains(qry.value(0).toString()) ? "Online"
                                                              : "Offline");
      model.push_back(tmp);
    }
  }
}

int UserDB::getAdminsCount() {
  QSqlQuery qry;
  qry.prepare("SELECT COUNT(*) FROM user WHERE utype=0");
  qry.exec();
  if (qry.next()) {
    return qry.value(0).toInt();
  }
  return 0;
}

int UserDB::getGamersCount() {
  QSqlQuery qry;
  qry.prepare("SELECT COUNT(*) FROM user WHERE utype=1");
  qry.exec();
  if (qry.next()) {
    return qry.value(0).toInt();
  }
  return 0;
}
