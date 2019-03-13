#include <QPropertyAnimation>

#include "RegisterDialog.h"
#include "RegisterDialog_ui.h"

RegisterDialog::RegisterDialog(QWidget* parent)
    : QDialog(parent), ui(new Ui::RegisterDialog) {
  ui->setupUi(this);
}

RegisterDialog::~RegisterDialog() {
  delete ui;
}
