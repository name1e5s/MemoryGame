#include "MainWindow.h"
#include <QDesktopWidget>
#include <QStyle>
#include <QLayout>
#include "ui_MainWindow.h"

MainWindow::MainWindow(QWidget* parent)
    : QMainWindow(parent), ui(new Ui::MainWindow) {
  ui->setupUi(this);
  setFixedSize(this->width(), this->height());
  setGeometry(QStyle::alignedRect(Qt::LeftToRight, Qt::AlignCenter,
                                  this->size(),
                                  qApp->desktop()->availableGeometry()));
}

MainWindow::~MainWindow() {
  delete ui;
}
