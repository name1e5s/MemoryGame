#include "client.h"
#include <utility.h>

Client *Client::_instance;

Client &Client::Instance() {
  if (_instance == 0)
    _instance = new Client;
  return *_instance;
}

static void onLoginResult(UNUSED SocketClient *client, std::string result) {
  QStringList resultList = QString::fromStdString(result).split('$');
  Client::Instance().emitLoginResult(
      resultList.at(0).toInt() == 0 ? false : true, resultList.at(1),
      resultList.at(2), resultList.at(3).toInt(), resultList.at(4).toInt());
}

static void onUid(UNUSED SocketClient *client, std::string result) {
  Client::Instance().setTag(QString::fromStdString(result).toUInt());
}

static void onRegisterResult(UNUSED SocketClient *client, std::string result) {
  Client::Instance().emitRegisterResult(
      QString::fromStdString(result).toInt() == 1 ? true : false);
}

static void onUpdateUserResult(UNUSED SocketClient *client,
                               std::string result) {
  Client::Instance().emitUpdateUserResult(
      QString::fromStdString(result).toInt() == 1 ? true : false);
}

static void onGetWordResult(UNUSED SocketClient *client, std::string result) {
  Client::Instance().emitGetWordResult(QString::fromStdString(result));
}

static void onAddWordResult(UNUSED SocketClient *client, std::string result) {
  Client::Instance().emitAddWordResult(
      QString::fromStdString(result).toInt() == 1 ? true : false);
}

static void onGetAdminsResult(UNUSED SocketClient *, std::string result) {
  Client::Instance().emitUpdateUserTable(QString::fromStdString(result));
}

static void onGetGamersResult(UNUSED SocketClient *, std::string result) {
  Client::Instance().emitUpdateUserTable(QString::fromStdString(result));
}

static void onSearchAdminsResult(UNUSED SocketClient *, std::string result) {
  Client::Instance().emitUpdateUserTable(QString::fromStdString(result));
}

static void onSearchGamersResult(UNUSED SocketClient *, std::string result) {
  Client::Instance().emitUpdateUserTable(QString::fromStdString(result));
}

static void onGetWordsResult(UNUSED SocketClient *, std::string result) {
  Client::Instance().emitUpdateWordTable(QString::fromStdString(result));
}

static void onSearchWordsResult(UNUSED SocketClient *, std::string result) {
  Client::Instance().emitUpdateWordTable(QString::fromStdString(result));
}

Client::Client(std::string address, int port, QObject *parent)
    : QObject(parent), SocketClient(address, port) {
  addListener("uid", onUid);
  addListener("loginResult", onLoginResult);
  addListener("registerResult", onRegisterResult);
  addListener("updateUserResult", onUpdateUserResult);
  addListener("getWordResult", onGetWordResult);
  addListener("addWordResult", onAddWordResult);
  addListener("getAdminsResult", onGetAdminsResult);
  addListener("getGamersResult", onGetGamersResult);
  addListener("getWordsResult", onGetWordsResult);
  addListener("searchAdminsResult", onSearchAdminsResult);
  addListener("searchGamersResult", onSearchGamersResult);
  addListener("searchWordsResult", onSearchWordsResult);
}
