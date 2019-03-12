#include <QMessageBox>

#include "Login.h"
#include "Login_ui.h"

LoginDialog::LoginDialog(QWidget* parent)
    : QDialog(parent), ui(new Ui::LoginDialog), reg(new RegisterDialog) {
  ui->setupUi(this);
  setFixedSize(this->width(), this->height());
  connect(ui->loginButton, &QtMaterialFlatButton::clicked, this,
          &LoginDialog::checkPassword);

  connect(ui->registerButton, &QtMaterialFlatButton::clicked, reg,
          &RegisterDialog::exec);
}

LoginDialog::~LoginDialog() {
  delete ui;
}

void LoginDialog::checkPassword() {
  if (ui->userName->text() == "test" && ui->passWord->text() == "test") {
    accept();
  } else {
    QMessageBox* msg = new QMessageBox;
    msg->setText("Login Failed.");
    msg->setWindowModality(Qt::NonModal);
    msg->setStandardButtons(QMessageBox::Close);
    msg->exec();
    reject();
  }
}
