#include <QMessageBox>
#include <QVariant>

#include <data/login.h>
#include <ui/Login.h>
#include <widgets/Login.h>

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
  auto fuck = Login::Instance().getGamer(ui->userName->text().toStdString(),
                                         ui->passWord->text().toStdString());
  if (fuck.first == Login::S_NOERROR) {
    QVariant data;
    data.setValue(fuck.second);
    emit sendGamer(data);
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
