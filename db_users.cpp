#include <QSqlRecord>
#include <QSqlField>
#include <table_model_user.h>
#include <db_user.h>

UserTableModel::UserTableModel(QObject *parent) : QmlAbstractTableModel(parent) {
    UserDB::Instance().getGamers(m_result);
}

void UserTableModel::searchGamer(QString query) {
    beginResetModel();
    m_result.clear();
    UserDB::Instance().searchGamers(m_result, query);
    endResetModel();
}

void UserTableModel::searchAdmin(QString query) {
    beginResetModel();
    m_result.clear();
    UserDB::Instance().searchAdmins(m_result, query);
    endResetModel();
}

