#ifndef BASICINFO_H
#define BASICINFO_H
#include <cstdint>
#include <json.hpp>
#include <string>

namespace Basic {
using nlohmann::json;
using std::string;
using uid_t = string;  // User id.
using pass_t = string; // md5 password

struct LoginInfo {
  uid_t uid;
  pass_t pass;
};

struct WordInfo {
public:
  WordInfo(const json &j) {
    word = j.at("word").get<string>();
    difficulty = j.at("difficulty").get<int>();
  }

  WordInfo(string word, int difficulty) : word(word), difficulty(difficulty) {}

  json toJson() { return json{{"word", word}, {"difficulty", difficulty}}; }
  string WordInfo::getWord() const { return word; }

  int WordInfo::getDifficulty() const { return difficulty; }

private:
  string word;
  int difficulty;
};

class BasePerson {
public:
  BasePerson(const json &j) {
    uid = j.at("uid").get<uid_t>();
    realName = j.at("name").get<string>();
  }

  BasePerson(uid_t uid, string realName) : uid(uid), realName(realName) {}

  virtual json toJson(void) = 0;

protected:
  uid_t uid;
  string realName;
};

class Gamer : public BasePerson {
  Gamer(const json &j) : BasePerson(j) {
    levelPassed = j.at("passed").get<uint32_t>();
    level = j.at("level").get<uint32_t>();
    exp = j.at("exp").get<uint32_t>();
  }
  Gamer(uid_t uid, string realName, uint32_t levelPassed, uint32_t level,
        uint32_t exp)
      : BasePerson(uid, realName), levelPassed(levelPassed), level(level),
        exp(exp) {}

  json toJson() {
    return json{{"uid", uid},
                {"name", realName},
                {"passed", levelPassed},
                {"level", level},
                {"exp", exp}};
  }

private:
  uint32_t levelPassed;
  uint32_t level;
  uint32_t exp;
};

class Admin : public BasePerson {
public:
  Admin(const json &j) : BasePerson(j) {
    level = j.at("level").get<uint32_t>();
    questionCount = j.at("count").get<uint32_t>();
  }

  Admin(uid_t uid, string realName, uint32_t level, uint32_t questionCount)
      : BasePerson(uid, realName), level(level), questionCount(questionCount) {}

  json toJson() {
    return json{{"uid", uid},
                {"name", realName},
                {"level", level},
                {"count", questionCount}};
  }

private:
  uint32_t level;
  uint32_t questionCount;
};
} // namespace Basic
#endif // BASICINFO_H
