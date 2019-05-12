#ifndef DB_WORD_H
#define DB_WORD_H
#include <QtSql>

class WordDB {
public:
  ~WordDB();
  static WordDB &Instance();
  QString getWord(int difficulty);
  bool addWord(QString word, QString uname, int difficulty);
  void getWords(QVector<QVector<QString>> &model);
  void searchWords(QVector<QVector<QString>> &model, QString query);

private:
  WordDB(const char *path = "./word.db");
  static WordDB *_instance;
  QSqlDatabase db;
};

#endif // DB_WORD_H
