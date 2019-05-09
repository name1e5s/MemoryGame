#include "db_word.h"

static QString difficulty[4] = {"", "Easy", "Normal", "Hard"};

WordDB *WordDB::_instance = 0;

WordDB &WordDB::Instance() {
  if (_instance == 0)
    _instance = new WordDB;
  return *_instance;
}

WordDB::~WordDB() { db.close(); }

WordDB::WordDB(const char *path) {
  if (QSqlDatabase::contains("qt_word_connection"))
    db = QSqlDatabase::database("qt_word_connection");
  else
    db = QSqlDatabase::addDatabase("QSQLITE", "qt_word_connection");
  db.setDatabaseName(path);
  if (!db.open()) {
    qDebug() << db.lastError();
  }

  QSqlQuery qry("qt_word_connection", db);
  qry.prepare("CREATE TABLE IF NOT EXISTS word ("
              "word TEXT PRIMARY KEY NOT NULL,"
              "uname TEXT NOT NULL,"
              "difficulty INT NOT NULL"
              ");");
  if (!qry.exec()) {
    qDebug() << QString::fromStdString(
        qry.lastError().driverText().toStdString());
    qDebug() << qry.executedQuery();
  }

  int count = 0;
  qry.prepare("SELECT COUNT(*) FROM word");
  qry.exec();
  if (qry.next()) {
    count = qry.value(0).toInt();
  }
  if (count == 0) {
    addWord("excited", "admin", 1);
    addWord("naive", "admin", 2);
    addWord("bravo", "admin", 3);
  }
}

QString WordDB::getWord(int difficulty) {
  QSqlQuery qry("qt_word_connection", db);
  QString qryStr = "SELECT word FROM word WHERE difficulty=%1 ORDER BY "
                   "RANDOM() LIMIT 1;";
  if (qry.exec(qryStr.arg(difficulty))) {
    if (qry.next()) {
      return qry.value(0).toString();
    }
  }
  return "SQL ERROR";
}

bool WordDB::addWord(QString word, QString uname, int difficulty) {
  QSqlQuery qry("qt_word_connection", db);
  QString qryStr = "INSERT INTO word (word, difficulty, uname) values "
                   "('%1',%2,'%3');";
  qry.prepare(qryStr.arg(word).arg(difficulty).arg(uname));
  return qry.exec();
}

void WordDB::searchWords(QVector<QVector<QString>> &model, QString query) {
  QString qryStr = "SELECT word, difficulty, uname FROM word WHERE %1";
  QSqlQuery qry("qt_word_connection", db);
  qry.prepare(qryStr.arg(query));
  if (qry.exec()) {
    while (qry.next()) {
      QVector<QString> tmp;
      tmp.push_back(qry.value(0).toString());
      tmp.push_back(difficulty[qry.value(1).toInt()]);
      tmp.push_back(qry.value(2).toString());
      model.push_back(tmp);
    }
  }
}

void WordDB::getWords(QVector<QVector<QString>> &model) {
  QString qryStr =
      "SELECT word, difficulty, uname FROM word ORDER BY difficulty";
  QSqlQuery qry("qt_word_connection", db);
  qry.prepare(qryStr);
  if (qry.exec()) {
    while (qry.next()) {
      QVector<QString> tmp;
      tmp.push_back(qry.value(0).toString());
      tmp.push_back(difficulty[qry.value(1).toInt()]);
      tmp.push_back(qry.value(2).toString());
      model.push_back(tmp);
    }
  }
}
