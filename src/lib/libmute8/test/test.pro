TARGET = test
TEMPLATE = app
CONFIG += testcase console

QT += testlib

SOURCES += \
    testcoreaudioimpl.cpp
HEADERS += \
    testcoreaudioimpl.h

include(../link.pri)
