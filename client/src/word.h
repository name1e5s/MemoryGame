#ifndef WORD_H
#define WORD_H
#include <BasicInfo.h>
#include <sqlite_modern_cpp.h>

class Word {
 public:
  static Word& Instance();
  static void destroy();

  void insert(const WordInfo& info, std::string author) {
    db << "INSERT INTO word (word, difficulty, author) values (?,?,?);"
       << info.word << info.difficulty << author;
  }

  void insert(const WordInfo& info) {
    db << "INSERT INTO word (word, difficulty) values (?,?);" << info.word
       << info.difficulty;
  }

  WordInfo nextWord(int difficulty) {
    WordInfo word;
    db << "SELECT word,difficulty FROM word WHERE difficulty=? ORDER BY "
          "RANDOM() LIMIT 1;"
       << difficulty >>
        [&](std::string w, int difficulty) {
          word.difficulty = difficulty;
          word.word = w;
        };
    return word;
  }

 private:
  Word(const std::string path = "word.db") : db(path) {
    db << "CREATE TABLE IF NOT EXISTS word ("
          "  _id integer primary key autoincrement not null,"
          "  word TEXT NOT NULL,"
          "  difficulty INT NOT NULL,"
          "  author TEXT"
          ");";
    int count = 0;
    db << "SELECT COUNT(*) FROM word" >> count;
    if (count == 0) {
      insert({"young", 1});
      insert({"simple", 2});
      insert({"naive", 3});
    }
  }

  sqlite::database db;
  static Word* _instance;
};
#endif  // WORD_H
