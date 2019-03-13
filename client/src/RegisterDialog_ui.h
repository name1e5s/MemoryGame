#ifndef UI_REGISTERDIALOG_H
#define UI_REGISTERDIALOG_H

#include <qtmaterialflatbutton.h>
#include <qtmaterialradiobutton.h>
#include <qtmaterialraisedbutton.h>
#include <qtmaterialtextfield.h>
#include <QLayout>
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
  QWidget* widget;
  QtMaterialRaisedButton* pushButton;
  QtMaterialRadioButton* radioButtonGamer;
  QtMaterialRadioButton* radioButtonAdmin;

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

    widget = new QWidget(RegisterDialog);
    // widget->setGeometry(QRect(370, 240, 240, 90));
    widget->move(370, 240);
    QVBoxLayout* buttonLayout = new QVBoxLayout;
    widget->setLayout(buttonLayout);

    radioButtonGamer = new QtMaterialRadioButton();
    radioButtonAdmin = new QtMaterialRadioButton();
    QWidget* container = new QWidget;
    QVBoxLayout* layout = new QVBoxLayout;
    container->setLayout(layout);
    layout->addWidget(radioButtonGamer);
    layout->addWidget(radioButtonAdmin);
    radioButtonAdmin->setText("Admin");
    radioButtonGamer->setText("Gamer");
    buttonLayout->addWidget(container);

    QSizePolicy policy;
    policy.setHorizontalPolicy(QSizePolicy::Maximum);
    container->setSizePolicy(policy);
    buttonLayout->setAlignment(Qt::AlignCenter);
    buttonLayout->setMargin(0);
    buttonLayout->setSpacing(0);

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
