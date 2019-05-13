#include <QDebug>
#include <common.h>
#include <db_user.h>
#include <db_word.h>
#include <request_handler.h>
#include <socket_client.h>
#include <socket_server.h>
#include <string>
#include <uid.h>
#include <utility.h>
#include <vector>

using std::vector;
vector<SocketClient *> RequestHandler::clients;

using namespace RequestHandler;

void broadCast(std::string key, std::string message, SocketClient *exception) {
  uint32_t _uid = exception->getTag();
  for (auto x : clients) {
    uint32_t uid = x->getTag();
    if ((uid) != (_uid)) {
      x->send(key, message);
    }
  }
}

static void onDisconnect(SocketClient *socket) {
  qDebug() << "Client" << socket->getTag() << "disconnected !";
  broadCast("message", {"Client disconnected"}, socket);
  uint32_t _uid = socket->getTag();
  for (unsigned int i = 0; i < clients.size(); i++) {
    uint32_t uid = clients[i]->getTag();
    if ((uid) != (_uid)) {
      clients.erase(clients.begin() + i);
    }
  }
  delete socket;
}

static void onLogin(SocketClient *client, std::string request) {
  QStringList requestList = QString::fromStdString(request).split('$');
  qDebug() << requestList;
  LoginRequest loginRequest = {requestList.at(0).toInt(), requestList.at(1),
                               requestList.at(2)};
  BaseUser user = UserDB::Instance().loginUser(loginRequest);
  int isSuccess = user.experience != -1;
  QString result = QString::number(isSuccess) + "$" + user.userName + "$" +
                   user.realName + "$" + QString::number(user.experience) +
                   "$" + QString::number(user.levelPassed);
  client->send("loginResult", result.toStdString());
}

static void onRegister(SocketClient *client, std::string request) {
  QStringList requestList = QString::fromStdString(request).split('$');
  RegisterRequest registerRequest = {requestList.at(0).toInt(),
                                     requestList.at(1), requestList.at(2),
                                     requestList.at(3)};
  int isSuccess = UserDB::Instance().registerUser(registerRequest) ? 1 : 0;
  client->send("registerResult", QString::number(isSuccess).toStdString());
}

static void onUpdateUser(SocketClient *client, std::string request) {
  QStringList requestList = QString::fromStdString(request).split('$');
  int isSuccess = UserDB::Instance().updateUser(requestList.at(0),
                                                requestList.at(1).toInt(),
                                                requestList.at(2).toInt())
                      ? 1
                      : 0;
  client->send("updateUserResult", QString::number(isSuccess).toStdString());
}

static void onGetWord(SocketClient *client, std::string request) {
  QStringList requestList = QString::fromStdString(request).split('$');
  qDebug() << requestList;
  client->send(
      "getWordResult",
      WordDB::Instance().getWord(requestList.at(0).toInt()).toStdString());
}

static void onAddWord(SocketClient *client, std::string request) {
  QStringList requestList = QString::fromStdString(request).split('$');
  int isSuccess =
      WordDB::Instance().addWord(requestList.at(0), requestList.at(1),
                                 requestList.at(2).toInt())
          ? 1
          : 0;
  client->send("addWordResult", QString::number(isSuccess).toStdString());
}

static void onGetAdmins(SocketClient *client, std::string request) {
  QVector<QVector<QString>> result;
  UserDB::Instance().getAdmins(result);
  client->send("getAdminsResult", QVecQVecStrToStdStr(result));
}

static void onGetGamers(SocketClient *client, std::string request) {
  QVector<QVector<QString>> result;
  UserDB::Instance().getGamers(result);
  client->send("getGamersResult", QVecQVecStrToStdStr(result));
  qDebug() << QString::fromStdString(QVecQVecStrToStdStr(result));
}

static void onGetWords(SocketClient *client, std::string request) {
  QVector<QVector<QString>> result;
  WordDB::Instance().getWords(result);
  client->send("getWordsResult", QVecQVecStrToStdStr(result));
}

static void onSearchAdmins(SocketClient *client, std::string request) {
  QVector<QVector<QString>> result;
  UserDB::Instance().searchAdmins(result, QString::fromStdString(request));
  client->send("searchAdminsResult", QVecQVecStrToStdStr(result));
}

static void onSearchGamers(SocketClient *client, std::string request) {
  QVector<QVector<QString>> result;
  UserDB::Instance().searchGamers(result, QString::fromStdString(request));
  client->send("searchGamersResult", QVecQVecStrToStdStr(result));
}

static void onSearchWords(SocketClient *client, std::string request) {
  QVector<QVector<QString>> result;
  WordDB::Instance().searchWords(result, QString::fromStdString(request));
  client->send("searchWordsResult", QVecQVecStrToStdStr(result));
}

void RequestHandler::initilizeClient(SocketClient *client) {
  client->setDisconnectListener(onDisconnect);
  client->addListener("loginRequest", onLogin);
  client->addListener("registerRequest", onRegister);
  client->addListener("updateUserRequest", onUpdateUser);
  client->addListener("getWordRequest", onGetWord);
  client->addListener("addWordRequest", onAddWord);
  client->addListener("getAdminsRequest", onGetAdmins);
  client->addListener("getGamersRequest", onGetGamers);
  client->addListener("getWordsRequest", onGetWords);
  client->addListener("searchAdminsRequest", onSearchAdmins);
  client->addListener("searchGamersRequest", onSearchGamers);
  client->addListener("searchWordsRequest", onSearchWords);
}
