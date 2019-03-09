#ifndef DIALOG_H
#define DIALOG_H

#include <QDialog>
#include "RegisterDialog.h"

namespace Ui {
class LoginDialog;
}

class LoginDialog : public QDialog {
  Q_OBJECT

 public:
  explicit LoginDialog(QWidget* parent = 0);
  ~LoginDialog();

 public slots:
  void checkPassword();

 private:
  Ui::LoginDialog* ui;
  RegisterDialog* reg;
};

#endif  // DIALOG_H
