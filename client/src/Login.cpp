#include "Login.h"
#include "Login_ui.h"

LoginDialog::LoginDialog(QWidget* parent)
    : QDialog(parent), ui(new Ui::LoginDialog) {
  ui->setupUi(this);
  setFixedSize(this->width(), this->height());
}

LoginDialog::~LoginDialog() {
  delete ui;
}
