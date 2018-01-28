TEMPLATE = subdirs

ext_qglobalshortcut.subdir = external/qglobalshortcut
ext_qglobalshortcut.target = qglobalshortcut

lib_mute8.subdir = lib/libmute8
lib_mute8.target = libmute8

SUBDIRS += \
    ext_qglobalshortcut \
    lib_mute8 \
    widget \
    app

app.depends = widget qglobalshortcut libmute8
