TEMPLATE = app
CONFIG += console c++11
CONFIG -= app_bundle
CONFIG -= qt

INCLUDEPATH += ../3rd_party/json

SOURCES += \
        main.cpp \
    BasicInfo.cpp

HEADERS += \
    BasicInfo.h
