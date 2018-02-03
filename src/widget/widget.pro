TEMPLATE = subdirs

SUBDIRS += \
    widget \
    plugin

plugin.depends = widget
