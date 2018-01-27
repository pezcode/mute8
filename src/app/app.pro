TARGET = mute8
TEMPLATE = app
CONFIG += windows

QT += core gui widgets

DEFINES += QT_DEPRECATED_WARNINGS

SOURCES += \
        main.cpp \
        settingswindow.cpp

HEADERS += \
        settingswindow.h

FORMS += \
        settingswindow.ui

include(../widget/audiodevicewidget.pri)
include(../lib/libmute8/libmute8.pri)
