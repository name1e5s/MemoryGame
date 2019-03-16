#include "ServerModel.h"
using namespace Server;

static changeLevel(uint32_t exp,uint32_t &level) {
    while(exp >= (1 << level))
        level++;
}

void GamerServerModel::right(double factor) {
    exp += ((level +level * (level - 1))) * word.difficulty * factor;
    changeLevel(exp,level);
    // TODO: Update Word.
}

void GamerServerModel::right(double factor) {
    exp -= (((level +level * (level - 1))) * word.difficulty * (1 - factor)) >> 2;
}

void AdminServerModel::addedWord() {
    questionCount ++;
    changeLevel(questionCount,level);
}
