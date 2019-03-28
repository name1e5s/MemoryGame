#ifndef GAMERS_H
#define GAMERS_H

#include <QDialog>

namespace Ui {
class Gamers;
}

class Gamers : public QDialog {
  Q_OBJECT

 public:
  explicit Gamers(QWidget* parent = 0);
  ~Gamers();

 private:
  Ui::Gamers* ui;
};

#endif  // GAMERS_H
