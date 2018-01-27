TARGET = test
TEMPLATE = app
CONFIG += testcase

QT += testlib

SOURCES += \
    tests.cpp \
    CoreAudio/testcoreaudiodevice.cpp \
    CoreAudio/testcorevolumecontrol.cpp \
    CoreAudio/testcoredeviceenumerator.cpp

HEADERS += \
    CoreAudio/testcoreaudiodevice.h \
    CoreAudio/testcorevolumecontrol.h \
    CoreAudio/testcoredeviceenumerator.h

include(../libmute8.pri)
