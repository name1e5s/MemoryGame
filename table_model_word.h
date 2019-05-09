#ifndef DB_WORDS_H
#define DB_WORDS_H
#include <table_model.h>

class WordTableModel : public QmlAbstractTableModel {
  Q_OBJECT

public:
  explicit WordTableModel(QObject *parent = nullptr);
  Q_INVOKABLE bool addWord(QString word, QString uname, int difficulty);
  Q_INVOKABLE void searchWords(QString query);
};

#endif // DB_WORDS_H
