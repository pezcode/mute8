TEMPLATE = subdirs

SUBDIRS += \
    qglobalshortcut \
    libmute8 \
    widget \
    app

qglobalshortcut.subdir = external/qglobalshortcut
libmute8.subdir = lib/libmute8

app.depends = widget qglobalshortcut libmute8

include(installer/installer.pri)
