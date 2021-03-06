TEMPLATE = app

QT += qml quick quickcontrols2 sql

CONFIG += c++11

SOURCES += main.cpp \
    table_model.cpp \
    client.cpp \
    table_model_user.cpp \
    table_model_word.cpp

RESOURCES += \  
    res.qrc

# Additional import path used to resolve QML modules in Qt Creator's code model
QML_IMPORT_PATH =

DISTFILES += \
    MemoryGame.qml

HEADERS += \
    common.h \
    table_model.h \
    table_model_user.h \
    table_model_word.h \
    client.h

INCLUDEPATH += ../socket

win32:CONFIG(release, debug|release): LIBS += -L$$PWD/../build-Socket-Desktop-Debug/release/ -lsocket
else:win32:CONFIG(debug, debug|release): LIBS += -L$$PWD/../build-Socket-Desktop-Debug/debug/ -lsocket
else:unix: LIBS += -L$$PWD/../build-Socket-Desktop-Debug/ -lsocket

INCLUDEPATH += $$PWD/.
DEPENDPATH += $$PWD/.

win32-g++:CONFIG(release, debug|release): PRE_TARGETDEPS += $$PWD/../build-Socket-Desktop-Debug/release/libsocket.a
else:win32-g++:CONFIG(debug, debug|release): PRE_TARGETDEPS += $$PWD/../build-Socket-Desktop-Debug/debug/libsocket.a
else:win32:!win32-g++:CONFIG(release, debug|release): PRE_TARGETDEPS += $$PWD/../build-Socket-Desktop-Debug/release/socket.lib
else:win32:!win32-g++:CONFIG(debug, debug|release): PRE_TARGETDEPS += $$PWD/../build-Socket-Desktop-Debug/debug/socket.lib
else:unix: PRE_TARGETDEPS += $$PWD/../build-Socket-Desktop-Debug/libsocket.a
