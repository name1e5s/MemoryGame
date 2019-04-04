#include <data/User.h>
#include <data/Word.h>

Word* Word::_instance = 0;

Word& Word::Instance() {
  if (_instance == 0)
    _instance = new Word;
  return *_instance;
}

Word::~Word() {
  db.close();
  delete _instance;
}

Login* Login::_instance = 0;

Login& Login::Instance() {
  if (_instance == 0)
    _instance = new Login;
  return *_instance;
}

Login::~Login() {
  db.close();
  delete _instance;
}
