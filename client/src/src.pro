QT += core gui widgets
TEMPLATE = app
CONFIG += c++14

TARGET = client

LIBS += $$top_builddir/components/$(OBJECTS_DIR)/libcomponents.a
INCLUDEPATH += $$top_srcdir/components/
INCLUDEPATH += ../../3rd_party/sqlite_modern_cpp/hdr
PRE_TARGETDEPS = $$top_builddir/components/$(OBJECTS_DIR)/libcomponents.a
SOURCES += \
        main.cpp \
    MainWindow.cpp \
    Login.cpp \
    RegisterDialog.cpp \
    CustomWidget.cpp \
    QGameTextField.cpp \
    BasicInfo.cpp \
    DataBase.cpp

HEADERS += \
    MainWindow.h \
    Login.h \
    Login_ui.h \
    RegisterDialog.h \
    RegisterDialog_ui.h \
    CustomWidget.h \
    QGameTextField.h \
    login.h \
    word.h \
    BasicInfo.h

FORMS += \
    MainWindow.ui

RESOURCES += \
    assets.qrc \
    ../../3rd_party/qt-material-widgets/components/resources.qrc # I hate QMAKE

unix: CONFIG += link_pkgconfig
unix: PKGCONFIG += sqlite3
