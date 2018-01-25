TARGET = test
TEMPLATE = app
CONFIG += testcase

QT += testlib

SOURCES += \
    tests.cpp \
    CoreAudio/testcoreenumerator.cpp \
    CoreAudio/testcoreaudiodevice.cpp \
    CoreAudio/testcorevolumecontrol.cpp

HEADERS += \
    CoreAudio/testcoreenumerator.h \
    CoreAudio/testcoreaudiodevice.h \
    CoreAudio/testcorevolumecontrol.h

include(../link.pri)
