#ifndef UI_DIALOG_H
#define UI_DIALOG_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QDialog>
#include <QtWidgets/QLabel>
#include <QtWidgets/QPushButton>

#include <qtmaterialflatbutton.h>
#include <qtmaterialtextfield.h>

QT_BEGIN_NAMESPACE

class LoginDialog_UI {
 public:
  QLabel* label;
  QtMaterialTextField* userName;
  QtMaterialTextField* passWord;
  QtMaterialFlatButton* loginButton;
  QtMaterialFlatButton* registerButton;

  void setupUi(QDialog* Dialog) {
    Dialog->setObjectName(QString::fromUtf8("Login"));
    Dialog->resize(640, 480);
    Dialog->setStyleSheet(QString::fromUtf8("QObject {background: white;}"));

    label = new QLabel(Dialog);
    label->setObjectName(QString::fromUtf8("label"));
    label->setGeometry(QRect(170, 10, 281, 251));
    label->setPixmap(QPixmap(QString::fromUtf8(":/logo/assets/logo.png")));

    userName = new QtMaterialTextField(Dialog);
    userName->setGeometry(QRect(210, 280, 220, 48));
    userName->setLabel("User Name");

    passWord = new QtMaterialTextField(Dialog);
    passWord->setGeometry(QRect(210, 340, 220, 48));
    passWord->setLabel("Password");
    passWord->setEchoMode(QLineEdit::Password);

    loginButton = new QtMaterialFlatButton(Dialog);
    loginButton->setGeometry(QRect(210, 410, 105, 32));
    loginButton->setBackgroundMode(Qt::OpaqueMode);

    registerButton = new QtMaterialFlatButton(Dialog);
    registerButton->setGeometry(QRect(335, 410, 105, 32));
    registerButton->setBackgroundMode(Qt::OpaqueMode);

    retranslateUi(Dialog);
  }

  void retranslateUi(QDialog* Dialog) {
    Dialog->setWindowTitle(QApplication::translate("Login", "Login", nullptr));
    label->setText(QString());
    loginButton->setText(QApplication::translate("Login", "Login", nullptr));
    registerButton->setText(
        QApplication::translate("Login", "Register", nullptr));
  }
};

namespace Ui {
class LoginDialog : public LoginDialog_UI {};
}  // namespace Ui

QT_END_NAMESPACE

#endif  // UI_DIALOG_H
