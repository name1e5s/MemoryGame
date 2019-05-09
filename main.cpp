#include <QGuiApplication>
#include <QQmlApplicationEngine>
#include <QQmlEngine>
#include <QQmlContext>
#include <QQuickStyle>
#include <db_user.h>
#include <table_model_user.h>
#include <table_model_word.h>
#include <login_handler.h>
#include <admin_handler.h>
#include <gamer_handler.h>

int main(int argc, char *argv[])
{
    UserDB db = UserDB::Instance();
    LoginHandler LoginHandler;
    QGuiApplication app(argc, argv);

    QQuickStyle::setStyle("Material");
    QQmlApplicationEngine engine;
    engine.load(QUrl(QStringLiteral("qrc:/ui/ui/MemoryGame.qml")));
    engine.rootContext()->setContextProperty("login_handler", &LoginHandler);
    qmlRegisterType<GamerHandler>("com.name1e5s.game", 1, 0, "GameHandler");
    qmlRegisterType<AdminHandler>("com.name1e5s.game", 1, 0, "AdminHandler");

    qmlRegisterType<UserTableModel>("com.name1e5s.game", 1, 0, "UserTableModel");
    qmlRegisterType<WordTableModel>("com.name1e5s.game", 1, 0, "WordTableModel");

    return app.exec();
}
