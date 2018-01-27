TARGET = libmute8
TEMPLATE = lib
CONFIG += static

SOURCES += \
    impl/CoreAudio/deviceenumerator.cpp \
    impl/CoreAudio/audiodevice.cpp \
    impl/CoreAudio/volumecontrol.cpp

HEADERS += \
    ../include/iaudiodevice.h \
    ../include/ideviceenumerator.h \
    ../include/ivolumecontrol.h \
    ../include/impl/CoreAudio/deviceenumerator.h \
    ../include/impl/CoreAudio/audiodevice.h \
    ../include/impl/CoreAudio/volumecontrol.h

INCLUDEPATH += \
    ../include \
    $$(BOOST_DIR)
