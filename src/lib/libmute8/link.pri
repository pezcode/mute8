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

PRE_TARGETDEPS += $$shadowed(lib)

# TODO: find a way to not hardcode this
LIBS += -L$$(BOOST_DIR)/lib64-msvc-14.1

INCLUDEPATH += \
    $$PWD/include \
    $$(BOOST_DIR)

DEPENDPATH += $$PWD/include
