#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <data/BasicInfo.h>
#include <QDebug>
#include <QMainWindow>
#include "CustomWidget.h"
#include "QGameTextField.h"

namespace Ui {
class GameWindow;
}

class GameWindow : public QMainWindow {
  Q_OBJECT

 public:
  explicit GameWindow(QWidget* parent = 0);
  ~GameWindow();

 signals:
  void gamerChanged();

 public slots:
  void setGamer(QVariant data) {
    gamer = data.value<Gamer>();
    updateUI();
  }
  void updateUI();
  void onRightAnswer();
  void onWrongAnswer();
  void onGameOver();
  void gamerTable();
  void setDifficulty(int difficulty);

 private:
  Ui::GameWindow* ui;
  CustomWidget* customWidget;
  QGameTextField* gameTextField;
  Gamer gamer;
};

#endif  // MAINWINDOW_H
