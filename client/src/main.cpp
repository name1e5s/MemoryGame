#include <widgets/GameWindow.h>
#include <widgets/Login.h>
#include <QApplication>
#include <QWidget>

int main(int argc, char* argv[]) {
  QApplication a(argc, argv);
  GameWindow w;
  LoginDialog d;
  QObject::connect(&d, &LoginDialog::sendGamer, &w, &GameWindow::setGamer);
  if (d.exec() != QDialog::Accepted) {
    return 1;
  }
  w.show();

  return a.exec();
}
