#include <QPropertyAnimation>

#include "RegisterDialog.h"
#include "RegisterDialog_ui.h"

RegisterDialog::RegisterDialog(QWidget* parent)
    : QDialog(parent), ui(new Ui::RegisterDialog) {
  ui->setupUi(this);
  QPropertyAnimation* animation =
      new QPropertyAnimation((ui->pushButton), "backgroundColor");
  animation->setDuration(10000);
  animation->setStartValue(QColor(0, 96, 88));
  animation->setEndValue(QColor(200, 0, 0));
  animation->start();
}

RegisterDialog::~RegisterDialog() {
  delete ui;
}
