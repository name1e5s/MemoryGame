#include "ServerModel.h"
#include <word.h>
using namespace Server;

static void changeLevel(int exp, int &level) {
  while (exp >= (1U << level))
    level++;
}

void GamerServerModel::right(double factor) {
  gamer.exp += ((gamer.level + gamer.level * (gamer.level - 1))) *
               word.difficulty * factor;
  changeLevel(gamer.exp, gamer.level);
  setWordInfo(Word::Instance().nextWord(gamer.currDifficulty));
}

void GamerServerModel::wrong(double factor) {
  gamer.exp -= uint32_t((((gamer.level + gamer.level * (gamer.level - 1))) *
                         word.difficulty * (1 - factor))) >>
               2;
}

void GamerServerModel::setWordInfo(Basic::WordInfo &&word) {
  this->word = word;
}

void AdminServerModel::addedWord() {
  admin.questionCount++;
  changeLevel(admin.questionCount, admin.level);
}
