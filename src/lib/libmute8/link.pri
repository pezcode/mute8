win32 {
    CONFIG(release, debug|release) {
        LIBS += -L$$shadowed(lib/release) -llibmute8
    }
    CONFIG(debug, debug|release) {
        LIBS += -L$$shadowed(lib/debug) -llibmute8
    }
} else {
    LIBS += -L$$shadowed(lib) -llibmute8
}

INCLUDEPATH += $$PWD/include
DEPENDPATH += $$PWD/include
