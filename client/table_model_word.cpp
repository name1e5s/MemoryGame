#include <client.h>
#include <table_model_word.h>

WordTableModel::WordTableModel(QObject *parent)
    : QmlAbstractTableModel(parent) {}

void WordTableModel::init() {
  Client::Instance().sendRequest("getWordsRequest", "");
}

int getDifficulty(QString s) {
  if (s.length() >= 7) {
    return 3;
  } else if (s.length() >= 4) {
    return 2;
  }
  return 1;
}

void WordTableModel::addWord(QString word, QString uname) {
  Client::Instance().sendRequest("addWordRequest",
                                 word + "$" + uname + "$" +
                                     QString::number(getDifficulty(word)));
  init();
}

void WordTableModel::searchWords(QString query) {
  Client::Instance().sendRequest("searchWordsRequest", query);
}
