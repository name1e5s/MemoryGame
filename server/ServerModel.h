#ifndef SERVERVIEW_H
#define SERVERVIEW_H

#include <BasicInfo.h>
#include <bits/stdc++.h>
namespace Server {
using std::string;

class GamerServerModel : public Basic::Gamer {
  using Gamer::Gamer;

public:
  void right(double factor);
  void wrong(double factor);
  void setWordInfo(Basic::WordInfo &&word);

private:
  Basic::WordInfo word;
};

class AdminServerModel : public Basic::Admin {
  using Admin::Admin;

public:
  void addedWord();
};
} // namespace Server

#endif // SERVERVIEW_H
