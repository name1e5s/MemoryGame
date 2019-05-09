#include "gamer_handler.h"
#include <db_user.h>
#include <db_word.h>

GamerHandler::GamerHandler(QObject *parent) : UserHandler(parent) {}

QString GamerHandler::getNewWord(int difficulty) {
  return WordDB::Instance().getWord(difficulty);
}
