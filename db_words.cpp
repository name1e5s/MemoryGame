#include <db_word.h>
#include <table_model_word.h>

WordTableModel::WordTableModel(QObject *parent)
    : QmlAbstractTableModel(parent) {
  WordDB::Instance().getWords(m_result);
}

int getDifficulty(QString s) {
  if (s.length() >= 7) {
    return 3;
  } else if (s.length() >= 4) {
    return 2;
  }
  return 1;
}

bool WordTableModel::addWord(QString word, QString uname) {
  beginResetModel();
  m_result.clear();
  bool result = WordDB::Instance().addWord(word, uname, getDifficulty(word));
  WordDB::Instance().getWords(m_result);
  endResetModel();
  return result;
}

void WordTableModel::searchWords(QString query) {
  beginResetModel();
  m_result.clear();
  WordDB::Instance().searchWords(m_result, query);
  endResetModel();
}
