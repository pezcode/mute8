TEMPLATE = subdirs
CONFIG += ordered

SUBDIRS += widget

build_widget_plugin {
    SUBDIRS += plugin
}
