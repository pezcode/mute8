LIBPATH = $$shadowed(lib)
LIBNAME = libmute8
debug_and_release_target {
    CONFIG(release, debug|release): LIBPATH = $$LIBPATH/release
    CONFIG(debug,   debug|release): LIBPATH = $$LIBPATH/debug
}
LIBS += -L$$LIBPATH -l$$LIBNAME
PRE_TARGETDEPS += $$LIBPATH
INCLUDEPATH += \
    $$PWD/include \
    $$(BOOST_DIR)
