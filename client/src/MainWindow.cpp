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
  setFixedSize(this->width(), this->height());
  setGeometry(QStyle::alignedRect(Qt::LeftToRight, Qt::AlignCenter,
                                  this->size(),
                                  qApp->desktop()->availableGeometry()));
  connect(ui->startNewGameButton, &QPushButton::clicked, customWidget,
          &CustomWidget::rightColorAnimation);
  connect(ui->pauseGameButton, &QPushButton::clicked, customWidget,
          &CustomWidget::wrongColorAnimation);
}

MainWindow::~MainWindow() {
  delete ui;
}
