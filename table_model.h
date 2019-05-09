#ifndef TABLE_MODEL_H
#define TABLE_MODEL_H
#include <QObject>
#include <QSqlQueryModel>
#include <QVector>
#include <QtSql>

class QmlAbstractTableModel : public QAbstractTableModel {
  Q_OBJECT
  Q_PROPERTY(int column READ getColumn WRITE setColumn NOTIFY columnChanged)

public:
  explicit QmlAbstractTableModel(QObject *parent = nullptr);
  int rowCount(const QModelIndex & = QModelIndex()) const final;
  int columnCount(const QModelIndex & = QModelIndex()) const final;
  QVariant data(const QModelIndex &index, int role) const final;
  QHash<int, QByteArray> roleNames() const final {
    return {{Qt::DisplayRole, "display"}};
  }
  int getColumn() { return m_column; }

  void setColumn(int value) {
    if (m_column != value) {
      m_column = value;
      emit columnChanged();
    }
  }

signals:
  void columnChanged();

protected:
  int m_column;
  QVector<QVector<QString>> m_result;
};

#endif // TABLE_MODEL_H
