defineReplace(ospath) {
    path = $$1
    return($$shell_quote($$shell_path($$path)))
}

# tools

# skip bin, kit, version folder
CREATOR = $$[QT_INSTALL_BINS]/../../../Tools/QtInstallerFramework/3.0/bin/binarycreator
WINDEPLOY = $$[QT_INSTALL_BINS]/windeployqt

# input

CONFIGFILE = $$PWD/config/config.xml
PACKAGES = $$PWD/packages
BINARY = $$shadowed($$PWD/../app/release/mute8)
win32: BINARY = $${BINARY}.exe
TRANSLATIONS = $$shadowed($$PWD/../app/translations)

# output

OUTDIR = $$shadowed($$PWD) # $$OUT_PWD refers to the .pro this file gets included from, $$PWD is the folder of this .pri
OUTPACKAGES = $$shadowed($$PACKAGES)
PKG_BINARY = $$OUTPACKAGES/com.pezcode.mute8/data
PKG_TRANSLATIONS = $$OUTPACKAGES/com.pezcode.mute8.translations/data

# commands

# copy installer package meta data (in case of shadow build)
!equals(OUTPACKAGES, $$PACKAGES) {
    COMMANDS += $$QMAKE_MKDIR $$ospath($$OUTPACKAGES) && $$QMAKE_COPY_DIR $$ospath($$PACKAGES) $$ospath($$OUTPACKAGES) &&
}
# copy app executable
COMMANDS += $$QMAKE_MKDIR $$ospath($$PKG_BINARY) && $$QMAKE_COPY_FILE $$ospath($$BINARY) $$ospath($$PKG_BINARY) &&
# copy translations
COMMANDS += $$QMAKE_MKDIR $$ospath($$PKG_TRANSLATIONS) && $$QMAKE_COPY_DIR $$ospath($$TRANSLATIONS) $$ospath($$PKG_TRANSLATIONS/translations) &&
# copy and patch Qt dlls and compiler runtime on Windows
win32 {
    COMMANDS += $$ospath($$WINDEPLOY) --no-translations --no-system-d3d-compiler --no-opengl-sw $$ospath($$PKG_BINARY/mute8.exe) &&
}
# make the installer!
COMMANDS += $$ospath($$CREATOR) --offline-only -c $$ospath($$CONFIGFILE) -p $$ospath($$OUTPACKAGES) $$ospath($$OUTDIR/setup)

# target

installer.target = installer
installer.depends = sub-app # app is a subdirs target in our main .pro
installer.commands = $$COMMANDS

QMAKE_EXTRA_TARGETS += installer
POST_TARGETDEPS += installer
