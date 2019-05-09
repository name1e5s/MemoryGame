#ifndef USER_HANDLER_H
#define USER_HANDLER_H
#include <common.h>
#include <QObject>

class UserHandler : public QObject, BaseUser
{
    Q_OBJECT
    Q_PROPERTY(QString userName READ getUserName WRITE setUserName NOTIFY userNameChanged)
    Q_PROPERTY(QString realName READ getRealName WRITE setRealName NOTIFY realNameChanged)
    Q_PROPERTY(int levelPassed READ getLevelPassed WRITE setLevelPassed NOTIFY levelPassedChanged)
    Q_PROPERTY(int experience READ getExperience WRITE setExperience NOTIFY experienceChanged)

public:
    explicit UserHandler(QObject *parent = nullptr);
    QString getUserName() const;
    void setUserName(QString userName);
    QString getRealName() const;
    void setRealName(QString realName);
    int getLevelPassed() const;
    void setLevelPassed(int levelPassed);
    int getExperience() const;
    void setExperience(int experience);
    Q_INVOKABLE void updateUser();

signals:
    void userNameChanged();
    void realNameChanged();
    void levelPassedChanged();
    void experienceChanged();
};

#endif // USER_HANDLER_H
