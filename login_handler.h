#ifndef LOGIN_HANDLER_H
#define LOGIN_HANDLER_H
#include <common.h>
#include <QObject>

class LoginHandler : public QObject{
    Q_OBJECT

public:
    explicit LoginHandler(QObject *parent = nullptr);
    Q_INVOKABLE bool login(int userType, QString userName, QString userPassword);
    Q_INVOKABLE bool regis(int userType, QString userName, QString userRealName, QString userPassword);
    Q_INVOKABLE QString getUserName();
    Q_INVOKABLE QString getRealName();
    Q_INVOKABLE int getLevelPassed();
    Q_INVOKABLE int getExperience();

private:
    LoginRequest m_loginRequest;
    RegisterRequest m_registerRequest;
    BaseUser m_baseUser;
};
#endif // LOGIN_HANDLER_H
