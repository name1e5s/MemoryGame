#include <QDebug>
#include <QDesktopWidget>
#include <QLayout>
#include <QPropertyAnimation>
#include <QStyle>

#include <data/Word.h>
#include <widgets/CustomWidget.h>
#include <widgets/MainWindow.h>
#include <widgets/QGameTextField.h>

#include "ui_MainWindow.h"

MainWindow::MainWindow(QWidget* parent)
    : QMainWindow(parent), ui(new Ui::MainWindow) {
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
          &MainWindow::onRightAnswer);
  connect(gameTextField, &QGameTextField::wrong, this,
          &MainWindow::onWrongAnswer);
  connect(ui->showAnswer, &QPushButton::clicked, gameTextField,
          &QGameTextField::showAnswer);
  connect(ui->gameOver, &QPushButton::clicked, gameTextField,
          &QGameTextField::gameOver);
  connect(ui->diffi, qOverload<int>(&QSpinBox::valueChanged), this,
          &MainWindow::setDifficulty);
  connect(this, &MainWindow::gamerChanged, this, &MainWindow::updateUI);

  setFixedSize(this->width(), this->height());
  setGeometry(QStyle::alignedRect(Qt::LeftToRight, Qt::AlignCenter,
                                  this->size(),
                                  qApp->desktop()->availableGeometry()));
}

MainWindow::~MainWindow() {
  delete ui;
}

void MainWindow::updateUI() {
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

void MainWindow::onRightAnswer() {
  gamer.exp += ((gamer.level * 2 + 1)) * gamer.currDifficulty;
  changeLevel(gamer.exp, gamer.level);
  emit gamerChanged();
}

void MainWindow::onWrongAnswer() {
  int tmp = gamer.exp - ((((gamer.level + gamer.level * (gamer.level - 1))) *
                          gamer.currDifficulty) >>
                         4);
  gamer.exp = tmp > 0 ? tmp : 0;
  changeLevel(gamer.exp, gamer.level);
  emit gamerChanged();
}

void MainWindow::setDifficulty(int difficulty) {
  gamer.currDifficulty = difficulty;
  gameTextField->setDifficulty(difficulty);
  emit gamerChanged();
}
