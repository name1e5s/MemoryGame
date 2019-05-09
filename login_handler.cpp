#include <QDebug>
#include <db_user.h>

#include <login_handler.h>

LoginHandler::LoginHandler(QObject *parent) : QObject(parent) {}

bool LoginHandler::login(int userType, QString userName, QString userPassword) {
  m_loginRequest.userType = userType;
  m_loginRequest.userName = userName;
  m_loginRequest.userPassword = userPassword;
  m_baseUser = UserDB::Instance().loginUser(m_loginRequest);
  if (m_baseUser.experience == -1) {
    return false;
  } else
    return true;
}

bool LoginHandler::regis(int userType, QString userName, QString userRealName,
                         QString userPassword) {
  m_registerRequest.userType = userType;
  m_registerRequest.userName = userName;
  m_registerRequest.realName = userRealName;
  m_registerRequest.userPassword = userPassword;
  return UserDB::Instance().registerUser(m_registerRequest);
}

QString LoginHandler::getUserName() { return this->m_baseUser.userName; }

QString LoginHandler::getRealName() { return this->m_baseUser.realName; }

int LoginHandler::getLevelPassed() { return this->m_baseUser.levelPassed; }

int LoginHandler::getExperience() { return this->m_baseUser.experience; }
