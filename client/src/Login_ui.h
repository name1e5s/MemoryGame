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
  QtMaterialFlatButton* pushButton;

  void setupUi(QDialog* Dialog) {
    Dialog->setObjectName(QString::fromUtf8("Login"));
    Dialog->resize(640, 480);
    Dialog->setStyleSheet(QString::fromUtf8("QObject {background: white;}"));

    label = new QLabel(Dialog);
    label->setObjectName(QString::fromUtf8("label"));
    label->setGeometry(QRect(170, 10, 281, 251));
    label->setPixmap(QPixmap(QString::fromUtf8(":/logo/assets/logo.png")));

    userName = new QtMaterialTextField(Dialog);
    userName->setGeometry(QRect(210, 280, 221, 48));
    userName->setLabel("User Name");

    passWord = new QtMaterialTextField(Dialog);
    passWord->setGeometry(QRect(210, 340, 221, 48));
    passWord->setLabel("Password");

    pushButton = new QtMaterialFlatButton(Dialog);
    pushButton->setGeometry(QRect(250, 410, 141, 36));
    pushButton->setBackgroundMode(Qt::OpaqueMode);

    retranslateUi(Dialog);
  }

  void retranslateUi(QDialog* Dialog) {
    Dialog->setWindowTitle(
        QApplication::translate("Dialog", "Dialog", nullptr));
    label->setText(QString());
    pushButton->setText(QApplication::translate("Dialog", "Login", nullptr));
  }
};

namespace Ui {
class LoginDialog : public LoginDialog_UI {};
}  // namespace Ui

QT_END_NAMESPACE

#endif  // UI_DIALOG_H
