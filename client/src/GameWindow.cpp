#include <QDebug>
#include <QDesktopWidget>
#include <QLayout>
#include <QPropertyAnimation>
#include <QStyle>

#include <data/Word.h>
#include <data/login.h>
#include <widgets/CustomWidget.h>
#include <widgets/GameWindow.h>
#include <widgets/QGameTextField.h>

#include "Gamers.h"
#include "ui_GameWindow.h"

GameWindow::GameWindow(QWidget* parent)
    : QMainWindow(parent), ui(new Ui::GameWindow) {
  ui->setupUi(this);

  customWidget = new CustomWidget(this);
  customWidget->setObjectName(QString::fromUtf8("customWidget"));
  customWidget->setGeometry(QRect(0, 80, 1080, 640));
  customWidget->setAutoFillBackground(true);

  gameTextField = new QGameTextField(customWidget);
  gameTextField->setObjectName(QString::fromUtf8("gameTextField"));
  gameTextField->setGeometry(QRect(50, 220, 980, 200));
  gameTextField->setStyleSheet(
      QString("background:transparent; color: white;border: none;"));
  gameTextField->setAlignment(Qt::AlignCenter);
  gameTextField->setFont(QFont("Roboto", 72, QFont::Medium));

  gameTextField->setAnswer(
      QString::fromStdString(Word::Instance().nextWord(1).word));
  gameTextField->setDifficulty(1);

  gameTextField->setFocus(Qt::OtherFocusReason);

  connect(gameTextField, &QGameTextField::right, customWidget,
          &CustomWidget::rightColorAnimation);
  connect(gameTextField, &QGameTextField::wrong, customWidget,
          &CustomWidget::wrongColorAnimation);
  connect(gameTextField, &QGameTextField::right, this,
          &GameWindow::onRightAnswer);
  connect(gameTextField, &QGameTextField::wrong, this,
          &GameWindow::onWrongAnswer);
  connect(ui->gameStart, &QPushButton::clicked, gameTextField,
          &QGameTextField::gameStart);
  connect(ui->gameOver, &QPushButton::clicked, gameTextField,
          &QGameTextField::gameOver);
  connect(ui->gameOver, &QPushButton::clicked, this, &GameWindow::onGameOver);
  connect(this, &GameWindow::destroyed, this, &GameWindow::onGameOver);
  connect(ui->diffi, qOverload<int>(&QSpinBox::valueChanged), this,
          &GameWindow::setDifficulty);
  connect(this, &GameWindow::gamerChanged, this, &GameWindow::updateUI);
  connect(ui->gamers, &QPushButton::clicked, this, &GameWindow::gamerTable);

  setFixedSize(this->width(), this->height());
  setGeometry(QStyle::alignedRect(Qt::LeftToRight, Qt::AlignCenter,
                                  this->size(),
                                  qApp->desktop()->availableGeometry()));
}

GameWindow::~GameWindow() {
  delete ui;
}

void GameWindow::updateUI() {
  ui->userName->setText("User Name: " + QString::fromStdString(gamer.uid));
  ui->userLevel->setText(QString("User Level: %1").arg(gamer.level));
  ui->userExp->setText(QString("User Exp: %1").arg(gamer.exp));
  qDebug() << "Out" << QString::fromStdString(gamer.uid);
}

// ==
static void changeLevel(int exp, int& level) {
  while ((uint)exp >= (1U << level))
    level++;
}

void GameWindow::onRightAnswer() {
  gamer.exp += ((gamer.level * 2 + 1)) * gamer.currDifficulty;
  changeLevel(gamer.exp, gamer.level);
  emit gamerChanged();
}

void GameWindow::onWrongAnswer() {
  int tmp = gamer.exp - ((((gamer.level + gamer.level * (gamer.level - 1))) *
                          gamer.currDifficulty) >>
                         4);
  gamer.exp = tmp > 0 ? tmp : 0;
  changeLevel(gamer.exp, gamer.level);
  emit gamerChanged();
}

void GameWindow::onGameOver() {
  Login::Instance().updateUser(gamer);
}

void GameWindow::setDifficulty(int difficulty) {
  gamer.currDifficulty = difficulty;
  gameTextField->setDifficulty(difficulty);
  emit gamerChanged();
}

void GameWindow::gamerTable() {
  QDialog* gamers = new Gamers(this);
  gamers->show();
}
