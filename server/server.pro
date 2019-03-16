TEMPLATE = app
CONFIG += console c++14
CONFIG -= app_bundle
CONFIG -= qt

INCLUDEPATH += ../3rd_party/json \
               ../3rd_party/sqlite_modern_cpp/hdr

SOURCES += \
        main.cpp \
    BasicInfo.cpp \
    Server.cpp \
    ServerModel.cpp

HEADERS += \
    BasicInfo.h \
    Socket.h \
    Server.h \
    ServerModel.h

unix: CONFIG += link_pkgconfig
unix: PKGCONFIG += sqlite3
