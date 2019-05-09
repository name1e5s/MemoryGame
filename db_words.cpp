#include <db_word.h>
#include <table_model_word.h>

WordTableModel::WordTableModel(QObject *parent)
    : QmlAbstractTableModel(parent) {
  WordDB::Instance().getWords(m_result);
}

bool WordTableModel::addWord(QString word, QString uname, int difficulty) {
  beginResetModel();
  m_result.clear();
  bool result = WordDB::Instance().addWord(word, uname, difficulty);
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
