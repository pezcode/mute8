# skip bin, kit, version folder
CREATOR = $$[QT_INSTALL_BINS]/../../../Tools/QtInstallerFramework/3.0/bin/binarycreator

CONFIGFILE = $$PWD/config/config.xml
PACKAGESDIR = $$PWD/packages

installer.target = setup
installer.depends = app
installer.commands = $$shell_path($$CREATOR) --offline-only -c $$shell_quote($$CONFIGFILE) -p $$shell_quote($$PACKAGESDIR) $$shell_quote($$OUT_PWD/setup)
QMAKE_EXTRA_TARGETS += installer

PRE_TARGETDEPS += setup
