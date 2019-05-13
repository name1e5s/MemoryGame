#ifndef CLIENT_H
#define CLIENT_H
#include <QObject>
#include <QString>
#include <QVector>
#include <socket_client.h>

class Client : public QObject, public SocketClient {
  Q_OBJECT
public:
  Q_INVOKABLE void sendRequest(QString requestKey, QString requestBody) {
    SocketClient::send(requestKey.toStdString(), requestBody.toStdString());
  }
  static Client &Instance();
  Client(std::string address = "127.0.0.1", int port = 8888,
         QObject *parent = nullptr);
  void emitLoginResult(bool isSuccess, QString userName, QString realName,
                       int exp, int levelPassed) {
    emit loginResult(isSuccess, userName, realName, exp, levelPassed);
  }
  void emitRegisterResult(bool isSuccess) { emit registerResult(isSuccess); }
  void emitUpdateUserResult(bool isSuccess) {
    emit updateUserResult(isSuccess);
  }
  void emitGetWordResult(QString word) { emit getWordResult(word); }
  void emitAddWordResult(bool isSuccess) { emit addWordResult(isSuccess); }
  void emitUpdateUserTable(QString result) { emit updateUserTable(result); }
  void emitUpdateWordTable(QString result) { emit updateWordTable(result); }
signals:
  void loginResult(bool isSuccess, QString userName, QString realName, int exp,
                   int levelPassed);
  void registerResult(bool isSuccess);
  void updateUserResult(bool isSuccess);
  void getWordResult(QString word);
  void addWordResult(bool isSuccess);
  void updateUserTable(QString result);
  void updateWordTable(QString result);

private:
  static Client *_instance;
};

#endif // CLIENT_H
