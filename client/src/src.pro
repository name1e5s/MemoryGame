QT += core gui widgets
TEMPLATE = app
CONFIG += c++11

TARGET = client

LIBS += $$top_builddir/components/$(OBJECTS_DIR)/libcomponents.a
INCLUDEPATH += $$top_srcdir/components/
PRE_TARGETDEPS = $$top_builddir/components/$(OBJECTS_DIR)/libcomponents.a
SOURCES += \
        main.cpp \
    MainWindow.cpp \
    Login.cpp

HEADERS += \
    MainWindow.h \
    Login.h \
    Login_ui.h

FORMS += \
    MainWindow.ui

RESOURCES += \
    assets.qrc
