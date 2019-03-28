#include <data/Word.h>
#include <data/login.h>

Word* Word::_instance = 0;

Word& Word::Instance() {
  if (_instance == 0)
    _instance = new Word;
  return *_instance;
}

void Word::destroy() {
  delete _instance;
}

Login* Login::_instance = 0;

Login& Login::Instance() {
  if (_instance == 0)
    _instance = new Login;
  return *_instance;
}

void Login::destroy() {
  db.close();
  delete _instance;
}
