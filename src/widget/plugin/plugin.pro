TARGET = audiodevicewidget
TARGET = $$qtLibraryTarget($$TARGET)
TEMPLATE = lib
CONFIG += plugin

# this plugin works in Qt Designer because it was compiled with the configured compiler toolset
# QtCreator uses its own plugins and the Windows version gets compiled with MSVC 32-bit

QT += widgets uiplugin

HEADERS +=  audiodevicewidgetplugin.h
SOURCES += audiodevicewidgetplugin.cpp

include(../audiodevicewidget.pri)

target.path = $$[QT_INSTALL_PLUGINS]/designer
INSTALLS += target
