TEMPLATE = app

QT += qml quick quickcontrols2 sql

CONFIG += c++11

SOURCES += main.cpp \
    db_user.cpp \
    gamer_handler.cpp \
    db_users.cpp \
    db_word.cpp \
    db_words.cpp \
    table_model.cpp \
    login_handler.cpp \
    user_handler.cpp \
    admin_handler.cpp

RESOURCES += \  
    res.qrc

# Additional import path used to resolve QML modules in Qt Creator's code model
QML_IMPORT_PATH =

DISTFILES += \
    MemoryGame.qml

HEADERS += \
    common.h \
    db_user.h \
    gamer_handler.h \
    db_word.h \
    table_model.h \
    login_handler.h \
    user_handler.h \
    admin_handler.h \
    table_model_user.h \
    table_model_word.h
