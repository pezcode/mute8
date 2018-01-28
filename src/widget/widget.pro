TEMPLATE = subdirs

SUBDIRS += widget
build_widget_plugin {
    SUBDIRS += plugin
    plugin.depends = widget
}
