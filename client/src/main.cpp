#include <widgets/Login.h>
#include <widgets/MainWindow.h>
#include <QApplication>
#include <QWidget>

int main(int argc, char* argv[]) {
  QApplication a(argc, argv);
  MainWindow w;
  LoginDialog d;
  QObject::connect(&d, &LoginDialog::sendGamer, &w, &MainWindow::setGamer);
  if (d.exec() != QDialog::Accepted) {
    return 1;
  }
  w.show();

  return a.exec();
}
