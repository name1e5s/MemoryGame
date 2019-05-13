#include <QSqlField>
#include <QSqlRecord>
#include <client.h>
#include <table_model_user.h>

UserTableModel::UserTableModel(QObject *parent)
    : QmlAbstractTableModel(parent) {}

void UserTableModel::init() {
  Client::Instance().sendRequest("getGamersRequest", "");
}

void UserTableModel::searchGamer(QString query) {
  Client::Instance().sendRequest("searchGamersRequest", query);
}

void UserTableModel::searchAdmin(QString query) {
  Client::Instance().sendRequest("searchAdminsRequest", query);
}
