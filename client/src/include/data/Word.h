#ifndef WORD_H
#define WORD_H
#include <QDebug>
#include <QtSql>
#include "BasicInfo.h"

class Word {
 public:
  static Word& Instance();
  ~Word();

  void insert(const WordInfo& info, std::string author) {
    QString str = QString(
                      "INSERT INTO word (word, difficulty, author) values "
                      "('%1',%2,'%3');")
                      .arg(QString::fromStdString(info.word))
                      .arg(info.difficulty)
                      .arg(QString::fromStdString(author));
    QSqlQuery qry("wordConnection", db);
    qry.prepare(str);
    qry.exec();
  }

  void insert(const WordInfo& info) {
    QString str =
        QString("INSERT INTO word (word, difficulty) values ('%1',%2);")
            .arg(QString::fromStdString(info.word))
            .arg(info.difficulty);
    QSqlQuery qry("wordConnection", db);
    qry.prepare(str);
    qry.exec();
  }

  WordInfo nextWord(int difficulty) {
    WordInfo word;
    QString str =
        "SELECT word,difficulty FROM word WHERE difficulty=%1 ORDER BY "
        "RANDOM() LIMIT 1;";
    QSqlQuery qry("wordConnection", db);
    if (qry.exec(str.arg(difficulty))) {
      if (qry.next()) {
        word.word = qry.value(0).toString().toStdString();
        word.difficulty = qry.value(1).toInt();
        return word;
      }
    }
    throw std::runtime_error("No Such Word!");
  }

  void getAdmins(QSqlQueryModel* model) {
    model->setQuery("SELECT word,difficulty,author FROM word", db);
  }

 private:
  Word(const char* path = "word.db") {
    if (QSqlDatabase::contains("wordConnection"))
      db = QSqlDatabase::database("wordConnection");
    else
      db = QSqlDatabase::addDatabase("QSQLITE", "wordConnection");
    db.setDatabaseName(path);
    if (!db.open()) {
      throw std::runtime_error(db.lastError().databaseText().toStdString());
    }
    QSqlQuery qry("wordConnection", db);
    qry.prepare(
        "CREATE TABLE IF NOT EXISTS word ("
        "  _id integer primary key autoincrement not null,"
        "  word TEXT NOT NULL,"
        "  difficulty INT NOT NULL,"
        "  author TEXT"
        ");");
    qry.exec();
    int count = 0;
    qry.prepare("SELECT COUNT(*) FROM word");
    qry.exec();
    if (qry.next()) {
      count = qry.value(0).toInt();
    }
    if (count == 0) {
      insert({"young", 1});
      insert({"simple", 2});
      insert({"naive", 3});
      insert({"6666", 1});
      insert({"excited", 1});
    }
  }

  QSqlDatabase db;
  static Word* _instance;
};
#endif  // WORD_H
