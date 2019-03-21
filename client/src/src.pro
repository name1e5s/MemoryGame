QT += core gui widgets
TEMPLATE = app
CONFIG += c++14

TARGET = client

LIBS += $$top_builddir/components/$(OBJECTS_DIR)/libcomponents.a
INCLUDEPATH += $$top_srcdir/components/ \
               include/
INCLUDEPATH += ../../3rd_party/sqlite_modern_cpp/hdr
PRE_TARGETDEPS = $$top_builddir/components/$(OBJECTS_DIR)/libcomponents.a
SOURCES += \
    main.cpp \
    MainWindow.cpp \
    Login.cpp \
    RegisterDialog.cpp \
    CustomWidget.cpp \
    QGameTextField.cpp \
    DB.cpp \
    BasicInfo.cpp

HEADERS += \
    include/data/BasicInfo.h \
    include/data/login.h \
    include/data/Word.h \
    include/ui/Login.h \
    include/ui/RegisterDialog.h \
    include/widgets/CustomWidget.h \
    include/widgets/Login.h \
    include/widgets/MainWindow.h \
    include/widgets/QGameTextField.h \
    include/widgets/RegisterDialog.h

FORMS += \
    MainWindow.ui

RESOURCES += \
    assets.qrc \
    ../../3rd_party/qt-material-widgets/components/resources.qrc # I hate QMAKE

unix: CONFIG += link_pkgconfig
unix: PKGCONFIG += sqlite3
