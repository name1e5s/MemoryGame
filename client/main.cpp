#include <QGuiApplication>
#include <QQmlApplicationEngine>
#include <QQmlContext>
#include <QQmlEngine>
#include <QQuickStyle>
#include <admin_handler.h>
#include <client.h>
#include <db_user.h>
#include <gamer_handler.h>
#include <login_handler.h>
#include <table_model_user.h>
#include <table_model_word.h>

int main(int argc, char *argv[]) {
  QGuiApplication app(argc, argv);
  Client::Instance().SocketClient::connect();
  UserDB db = UserDB::Instance();
  LoginHandler LoginHandler;
  UserTableModel userTableModel;
  userTableModel.setColumn(4);
  WordTableModel wordTableModel;
  wordTableModel.setColumn(3);
  qRegisterMetaType<QVector<QVector<QString>>>("QVector<QVector<QString>>");
  QObject::connect(&Client::Instance(), &Client::updateUserTable,
                   &userTableModel, &UserTableModel::onModelUpdate);
  QObject::connect(&Client::Instance(), &Client::updateWordTable,
                   &wordTableModel, &WordTableModel::onModelUpdate);
  userTableModel.init();
  wordTableModel.init();

  QQuickStyle::setStyle("Material");
  QQmlApplicationEngine engine;
  engine.rootContext()->setContextProperty("login_handler", &LoginHandler);
  qmlRegisterType<Client>("com.name1e5s.game", 1, 0, "Client");
  engine.rootContext()->setContextProperty("game_client", &Client::Instance());
  engine.rootContext()->setContextProperty("userTableModel", &userTableModel);
  engine.rootContext()->setContextProperty("wordTableModel", &wordTableModel);
  qmlRegisterType<GamerHandler>("com.name1e5s.game", 1, 0, "GameHandler");
  qmlRegisterType<AdminHandler>("com.name1e5s.game", 1, 0, "AdminHandler");
  qmlRegisterType<UserTableModel>("com.name1e5s.game", 1, 0, "UserTableModel");
  qmlRegisterType<WordTableModel>("com.name1e5s.game", 1, 0, "WordTableModel");
  engine.load(QUrl(QStringLiteral("qrc:/ui/ui/MemoryGame.qml")));

  return app.exec();
}
