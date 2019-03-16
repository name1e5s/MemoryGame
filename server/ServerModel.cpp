#include "ServerModel.h"
using namespace Server;

static void changeLevel(uint32_t exp,uint32_t &level) {
    while(exp >= (1U << level))
        level++;
}

void GamerServerModel::right(double factor) {
    exp += ((level +level * (level - 1))) * word.getDifficulty() * factor;
    changeLevel(exp,level);
    // TODO: Update Word.
}

void GamerServerModel::wrong(double factor) {
    exp -= uint32_t((((level +level * (level - 1))) * word.getDifficulty() * (1 - factor))) >> 2;
}

void AdminServerModel::addedWord() {
    questionCount ++;
    changeLevel(questionCount,level);
}
