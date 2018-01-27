win32 {
    CONFIG(release, debug|release) {
        LIBS += -L$$shadowed(widget/release) -laudiodevicewidget
    }
    CONFIG(debug, debug|release) {
        LIBS += -L$$shadowed(widget/debug) -laudiodevicewidget
    }
} else {
    LIBS += -L$$shadowed(widget) -laudiodevicewidget
}

PRE_TARGETDEPS += $$shadowed(widget)

INCLUDEPATH += $$PWD/widget
DEPENDPATH += $$PWD/widget
