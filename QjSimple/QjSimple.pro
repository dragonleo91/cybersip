DEFINES -= UNICODE
TEMPLATE = app
TARGET = QjSimple

QT += core \
    gui \
    network

HEADERS += buddy.h \
    PjCallback.h \
    accountdialog.h \
    debugdialog.h \
    addbuddydialog.h \
    imwidget.h \
    qjsimple.h

SOURCES += buddy.cpp \
    PjCallback.cpp \
    accountdialog.cpp \
    debugdialog.cpp \
    addbuddydialog.cpp \
    imwidget.cpp \
    main.cpp \
    qjsimple.cpp

FORMS += accountdialog.ui \
    debugdialog.ui \
    addbuddydialog.ui \
    imwidget.ui \
    qjsimple.ui

RESOURCES += icons.qrc
win32-g++:RC_FILE = appicon.rc

# PJ Headers.
INCLUDEPATH += ../pjproject/pjlib/include \
    ../pjproject/pjlib-util/include \
    ../pjproject/pjnath/include \
    ../pjproject/pjmedia/include \
    ../pjproject/pjsip/include

# PJ Libs.
LIBS += -L../pjproject/lib
LIBS += -llibpjproject-i386-Win32-vc8-Debug

# FFMPEG Libs.
LIBS += -L../ffmpeg/lib
LIBS += -L../BaseClasses/lib

# SDL Libs.
LIBS += -L../SDL/lib

# Windows Libs.
LIBS += -lws2_32

OTHER_FILES += Changelog
