TARGET = mute8
TEMPLATE = app
CONFIG += windows

QT += core gui widgets

# dependencies
include(../widget/audiodevicewidget.pri)
include(../lib/libmute8/libmute8.pri)
include(../external/qglobalshortcut/qglobalshortcut.pri)
include(../external/singleapplication/singleapplication.pri)

DEFINES += QT_DEPRECATED_WARNINGS

SOURCES += \
    main.cpp \
    settingswindow.cpp \
    trayapplication.cpp \
    mute8.cpp

HEADERS += \
    settingswindow.h \
    trayapplication.h \
    mute8.h

FORMS += \
    settingswindow.ui

RESOURCES += \
    resources.qrc

# Windows icon
RC_ICONS = resources/icons/app.ico
# macOS icon
ICON = resources/icons/app.icns

LANGUAGES = de
TRANSLATIONDIR = translations

for(lang, LANGUAGES){
    TRANSLATIONS += $${TRANSLATIONDIR}/mute8_$${lang}.ts
}

# lupdate parses everything in INCLUDEPATH (just adding boost makes it take 15 minutes)
# it checks TR_EXCLUDE for regular expressions to exclude from parsing
# so we add all the target's include paths to that list
# note: this assumes our own source files are not in the include path!
for(incl, INCLUDEPATH){
    TR_EXCLUDE += $$clean_path($$incl)/*
}

LUPDATE = $$shell_path($$[QT_INSTALL_BINS]/lupdate)
LRELEASE = $$shell_path($$[QT_INSTALL_BINS]/lrelease)

# update ts files after every compilation
QMAKE_POST_LINK = $${LUPDATE} $$_PRO_FILE_

# compile ts files into qm binaries
build_qm.input = TRANSLATIONS
build_qm.output  = $${TRANSLATIONDIR}/${QMAKE_FILE_IN_BASE}.qm
build_qm.commands = $${LRELEASE} ${QMAKE_FILE_IN} -qm ${QMAKE_FILE_OUT}
build_qm.CONFIG += no_link target_predeps
QMAKE_EXTRA_COMPILERS += build_qm
