#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <data/BasicInfo.h>
#include <QDebug>
#include <QMainWindow>
#include "CustomWidget.h"
#include "QGameTextField.h"

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow {
  Q_OBJECT

 public:
  explicit MainWindow(QWidget* parent = 0);
  ~MainWindow();

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
  void setDifficulty(int difficulty);

 private:
  Ui::MainWindow* ui;
  CustomWidget* customWidget;
  QGameTextField* gameTextField;
  Gamer gamer;
};

#endif  // MAINWINDOW_H
