#include "Login.h"
#include <QMessageBox>
#include "Login_ui.h"

LoginDialog::LoginDialog(QWidget* parent)
    : QDialog(parent), ui(new Ui::LoginDialog) {
  ui->setupUi(this);
  setFixedSize(this->width(), this->height());
  connect(ui->pushButton, &QtMaterialFlatButton::clicked, this,
          &LoginDialog::checkPassword);
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
