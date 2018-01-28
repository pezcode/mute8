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

RESOURCES += \
    resources.qrc

# Windows icon
RC_ICONS = resources/icons/app.ico
# macOS icon
ICON = resources/icons/app.icns

include(../widget/audiodevicewidget.pri)
include(../lib/libmute8/libmute8.pri)
include(../external/qglobalshortcut/qglobalshortcut.pri)
include(../external/singleapplication/singleapplication.pri)
