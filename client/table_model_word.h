#ifndef DB_WORDS_H
#define DB_WORDS_H
#include <table_model.h>

class WordTableModel : public QmlAbstractTableModel {
  Q_OBJECT

public:
  explicit WordTableModel(QObject *parent = nullptr);
  void init();
  Q_INVOKABLE void addWord(QString word, QString uname);
  Q_INVOKABLE void searchWords(QString query);
};

#endif // DB_WORDS_H
