#include "client.h"
#include <QDebug>
#include <utility.h>

Client *Client::_instance;

Client &Client::Instance() {
  if (_instance == 0)
    _instance = new Client;
  return *_instance;
}

static void onLoginResult(SocketClient *client, std::string result) {
  QStringList resultList = QString::fromStdString(result).split('$');
  Client::Instance().emitLoginResult(
      resultList.at(0).toInt() == 0 ? false : true, resultList.at(1),
      resultList.at(2), resultList.at(3).toInt(), resultList.at(4).toInt());
}

static void onUid(SocketClient *client, std::string result) {
  Client::Instance().setTag(QString::fromStdString(result).toUInt());
  qDebug() << "Uid" << Client::Instance().getTag();
}

static void onRegisterResult(SocketClient *client, std::string result) {
  Client::Instance().emitRegisterResult(
      QString::fromStdString(result).toInt() == 1 ? true : false);
}

static void onUpdateUserResult(SocketClient *client, std::string result) {
  Client::Instance().emitUpdateUserResult(
      QString::fromStdString(result).toInt() == 1 ? true : false);
}

static void onGetWordResult(SocketClient *client, std::string result) {
  Client::Instance().emitGetWordResult(QString::fromStdString(result));
}

static void onAddWordResult(SocketClient *client, std::string result) {
  Client::Instance().emitAddWordResult(
      QString::fromStdString(result).toInt() == 1 ? true : false);
}

static void onGetAdminsResult(SocketClient *, std::string result) {
  Client::Instance().emitUpdateUserTable(QString::fromStdString(result));
}

static void onGetGamersResult(SocketClient *, std::string result) {
  Client::Instance().emitUpdateUserTable(QString::fromStdString(result));
}

static void onSearchAdminsResult(SocketClient *, std::string result) {
  Client::Instance().emitUpdateUserTable(QString::fromStdString(result));
}

static void onSearchGamersResult(SocketClient *, std::string result) {
  Client::Instance().emitUpdateUserTable(QString::fromStdString(result));
}

static void onGetWordsResult(SocketClient *, std::string result) {
  Client::Instance().emitUpdateWordTable(QString::fromStdString(result));
}

static void onSearchWordsResult(SocketClient *, std::string result) {
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
