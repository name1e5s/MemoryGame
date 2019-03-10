#ifndef UI_REGISTERDIALOG_H
#define UI_REGISTERDIALOG_H

#include <qtmaterialflatbutton.h>
#include <qtmaterialtextfield.h>
#include <qtmaterialraisedbutton.h>
#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QDialog>
#include <QtWidgets/QFrame>
#include <QtWidgets/QLabel>

QT_BEGIN_NAMESPACE

class Ui_RegisterDialog {
 public:
  QLabel* label;
  QtMaterialTextField* userName;
  QtMaterialTextField* passWord;
  QtMaterialTextField* realName;
  QFrame* frame;
  QtMaterialRaisedButton* pushButton;

  void setupUi(QDialog* RegisterDialog) {
    RegisterDialog->resize(640, 480);
    RegisterDialog->setStyleSheet(
        QString::fromUtf8("QObject {background: white;}"));

    label = new QLabel(RegisterDialog);
    label->setGeometry(QRect(20, 90, 300, 300));
    label->setPixmap(QPixmap(QString::fromUtf8(":/logo/assets/logo.png")));

    userName = new QtMaterialTextField(RegisterDialog);
    userName->setGeometry(QRect(370, 80, 231, 48));
    userName->setLabel("User Name");

    passWord = new QtMaterialTextField(RegisterDialog);
    passWord->setGeometry(QRect(370, 133, 231, 48));
    passWord->setLabel("Password");

    realName = new QtMaterialTextField(RegisterDialog);
    realName->setGeometry(QRect(370, 186, 231, 48));
    realName->setLabel("Real Name");

    frame = new QFrame(RegisterDialog);
    frame->setGeometry(QRect(370, 230, 240, 111));
    frame->setFrameShape(QFrame::StyledPanel);
    frame->setFrameShadow(QFrame::Raised);

    pushButton = new QtMaterialRaisedButton(RegisterDialog);
    pushButton->setGeometry(QRect(370, 360, 240, 36));
    pushButton->setBackgroundMode(Qt::OpaqueMode);

    retranslateUi(RegisterDialog);
  }

  void retranslateUi(QDialog* RegisterDialog) {
    RegisterDialog->setWindowTitle(
        QApplication::translate("RegisterDialog", "Register", nullptr));
    label->setText(QString());
    pushButton->setText(
        QApplication::translate("RegisterDialog", "Register", nullptr));
  }
};

namespace Ui {
class RegisterDialog : public Ui_RegisterDialog {};
}  // namespace Ui

QT_END_NAMESPACE

#endif  // UI_REGISTERDIALOG_H
