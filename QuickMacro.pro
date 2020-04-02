#-------------------------------------------------
#
# Project created by QtCreator 2019-03-06T09:45:09
#
#-------------------------------------------------

QT       += core gui serialport
DEFINES-= UNICODE
greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = QuickMacro
TEMPLATE = app

# The following define makes your compiler emit warnings if you use
# any feature of Qt which has been marked as deprecated (the exact warnings
# depend on your compiler). Please consult the documentation of the
# deprecated API in order to know how to port your code away from it.
DEFINES += QT_DEPRECATED_WARNINGS

# You can also make your code fail to compile if you use deprecated APIs.
# In order to do so, uncomment the following line.
# You can also select to disable deprecated APIs only up to a certain version of Qt.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0


SOURCES += \
        main.cpp \
        window.cpp \
    global.cpp \
    hotkey/MyGlobalShortCut.cpp \
    hotkey/MyWinEventFilter.cpp \
    test.cpp \
    findgamewindow.cpp \
    worker/discern.cpp \
    worker/findicon.cpp \
    macro/tl.cpp \
    worker/findhp.cpp \
    macro/actuator.cpp

HEADERS += \
        window.h \
    global.h \
    hotkey/MyGlobalShortCut.h \
    hotkey/MyWinEventFilter.h \
    test.h \
    findgamewindow.h \
    worker/discern.h \
    worker/findicon.h \
    macro/tl.h \
    worker/findhp.h \
    macro/actuator.h

FORMS += \
        window.ui

RESOURCES += \
    file.qrc

DISTFILES +=
