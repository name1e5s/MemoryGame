TEMPLATE = app
CONFIG += console c++14
CONFIG -= app_bundle
CONFIG -= qt
QMAKE_LFLAGS += -L../3rd_party/handy/ -lhandy -pthread


INCLUDEPATH += ../3rd_party/json \
               ../3rd_party/sqlite_modern_cpp/hdr \
               ../3rd_party/handy/include

SOURCES += \
        main.cpp \
    BasicInfo.cpp \
    Server.cpp \
    ServerModel.cpp \
    Database.cpp


HEADERS += \
    BasicInfo.h \
    Server.h \
    ServerModel.h \
    word.h \
    login.h

unix: CONFIG += link_pkgconfig
unix: PKGCONFIG += sqlite3
