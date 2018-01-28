TARGET = audiodevicewidget
TEMPLATE = lib
CONFIG += static

QT += widgets

DEFINES += QDESIGNER_EXPORT_WIDGETS

HEADERS += \
    audiodevicewidget.h \
    levelmeter.h
SOURCES += \
    audiodevicewidget.cpp \
    levelmeter.cpp
