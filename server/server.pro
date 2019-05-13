QT -= gui
QT += sql

CONFIG += c++11 console
CONFIG -= app_bundle

# The following define makes your compiler emit warnings if you use
# any feature of Qt which as been marked deprecated (the exact warnings
# depend on your compiler). Please consult the documentation of the
# deprecated API in order to know how to port your code away from it.
DEFINES += QT_DEPRECATED_WARNINGS

# You can also make your code fail to compile if you use deprecated APIs.
# In order to do so, uncomment the following line.
# You can also select to disable deprecated APIs only up to a certain version of Qt.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

SOURCES += \
        main.cpp \
    db_user.cpp \
    db_word.cpp \
    uid.cpp \
    request_handler.cpp

HEADERS += \
    common.h \
    db_user.h \
    db_word.h \
    uid.h \
    db_word.h \
    request_handler.h

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
