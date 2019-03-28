#include <exception>

#include <data/login.h>
#include <ui/RegisterDialog.h>
#include <widgets/RegisterDialog.h>
#include <QMessageBox>
#include <QPropertyAnimation>

RegisterDialog::RegisterDialog(QWidget* parent)
    : QDialog(parent), ui(new Ui::RegisterDialog) {
  ui->setupUi(this);
  connect(ui->pushButton, &QtMaterialRaisedButton::clicked, this,
          &RegisterDialog::reg);
}

RegisterDialog::~RegisterDialog() {
  delete ui;
}

void RegisterDialog::reg() {
  bool flag = ui->radioButtonGamer->isChecked();
  try {
    Login::Instance().insert(ui->userName->text(), ui->passWord->text(),
                             flag ? 1 : 0, ui->realName->text());
    accept();
  } catch (std::exception& e) {
    QMessageBox* msg = new QMessageBox;
    msg->setText(QString("Register failed: %1").arg(e.what()));
    msg->setWindowModality(Qt::NonModal);
    msg->setStandardButtons(QMessageBox::Close);
    msg->exec();
  }
}
