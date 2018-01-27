TARGET = audiodevicewidget
TEMPLATE = lib
CONFIG += static
VERSION = 0.0.1

QT += widgets

DEFINES += QDESIGNER_EXPORT_WIDGETS

HEADERS += \
    audiodevicewidget.h \
    levelmeter.h
SOURCES += \
    audiodevicewidget.cpp \
    levelmeter.cpp
