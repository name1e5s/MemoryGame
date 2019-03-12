#include "MainWindow.h"
#include <QDesktopWidget>
#include <QLayout>
#include <QPropertyAnimation>
#include <QStyle>
#include "CustomWidget.h"
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

  gameTextField->setAnswer(QString("GO FUCK YOURSELF"));

  gameTextField->setFocus(Qt::OtherFocusReason);

  connect(gameTextField, &QGameTextField::right, customWidget,
          &CustomWidget::rightColorAnimation);
  connect(gameTextField, &QGameTextField::wrong, customWidget,
          &CustomWidget::wrongColorAnimation);

  setFixedSize(this->width(), this->height());
  setGeometry(QStyle::alignedRect(Qt::LeftToRight, Qt::AlignCenter,
                                  this->size(),
                                  qApp->desktop()->availableGeometry()));
}

MainWindow::~MainWindow() {
  delete ui;
}
