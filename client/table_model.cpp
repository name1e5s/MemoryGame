#include "table_model.h"

QmlAbstractTableModel::QmlAbstractTableModel(QObject *parent)
    : QAbstractTableModel(parent) {}

int QmlAbstractTableModel::rowCount(const QModelIndex &) const {
  return m_result.length();
}

int QmlAbstractTableModel::columnCount(const QModelIndex &) const {
  return m_column;
}

QVariant QmlAbstractTableModel::data(const QModelIndex &index, int role) const {
  switch (role) {
  case Qt::DisplayRole:
    return m_result.at(index.row()).at(index.column());
  default:
    break;
  }

  return QVariant();
}
