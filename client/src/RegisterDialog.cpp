#include <login.h>
#include <QPropertyAnimation>

#include "RegisterDialog.h"
#include "RegisterDialog_ui.h"

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
  Login::Instance().insert(ui->userName->text().toStdString(),
                           ui->passWord->text().toStdString(), flag ? 1 : 0,
                           ui->realName->text().toStdString());
  accept();
}
