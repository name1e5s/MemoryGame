QT += core gui widgets
TEMPLATE = app
CONFIG += c++11

TARGET = client

LIBS += $$top_builddir/components/$(OBJECTS_DIR)/libcomponents.a
INCLUDEPATH += $$top_srcdir/components/
PRE_TARGETDEPS = $$top_builddir/components/$(OBJECTS_DIR)/libcomponents.a
SOURCES += \
        main.cpp \
    MainWindow.cpp

HEADERS += \
    MainWindow.h

FORMS += \
    MainWindow.ui
