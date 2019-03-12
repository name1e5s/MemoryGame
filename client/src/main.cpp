#include <QApplication>

#include "Login.h"
#include "MainWindow.h"

int main(int argc, char* argv[]) {
  QApplication a(argc, argv);
  MainWindow w;
  LoginDialog d;
  if (d.exec() != QDialog::Accepted) {
    return 1;
  }
  w.show();

  return a.exec();
}
