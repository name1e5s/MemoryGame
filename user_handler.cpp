#include "user_handler.h"
#include <db_user.h>

UserHandler::UserHandler(QObject *parent) : QObject(parent) {
}

QString UserHandler::getUserName() const {
    return userName;
}

void UserHandler::setUserName(QString userName) {
    if(userName != this->userName) {
        this->userName = userName;
        emit userNameChanged();
    }
}

QString UserHandler::getRealName() const {
    return realName;
}

void UserHandler::setRealName(QString realName) {
    if(realName != this->realName) {
        this->realName = realName;
        emit realNameChanged();
    }
}

int UserHandler::getLevelPassed() const {
    return levelPassed;
}
void UserHandler::setLevelPassed(int levelPassed) {
    if(this->levelPassed != levelPassed) {
        this->levelPassed = levelPassed;
        emit levelPassedChanged();
    }
}

int UserHandler::getExperience() const {
    return experience;
}

void UserHandler::setExperience(int experience) {
    if(this->experience != experience) {
        this->experience = experience;
        emit experienceChanged();
    }
}

void UserHandler::updateUser() {
    UserDB::Instance().updateUser(this);
}
