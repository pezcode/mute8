#include <audiodevicewidget.h>
#include "audiodevicewidgetplugin.h"

#include <QtPlugin>

AudioDeviceWidgetPlugin::AudioDeviceWidgetPlugin(QObject *parent) : QObject(parent)
{

}

void AudioDeviceWidgetPlugin::initialize(QDesignerFormEditorInterface * /* core */)
{
    if (initialized)
        return;

    initialized = true;
}

bool AudioDeviceWidgetPlugin::isInitialized() const
{
    return initialized;
}

QWidget *AudioDeviceWidgetPlugin::createWidget(QWidget *parent)
{
    return new AudioDeviceWidget(parent);
}

QString AudioDeviceWidgetPlugin::name() const
{
    return QStringLiteral("AudioDevice");
}

QString AudioDeviceWidgetPlugin::group() const
{
    return QStringLiteral("Display Widgets");
}

QIcon AudioDeviceWidgetPlugin::icon() const
{
    return QIcon();
}

QString AudioDeviceWidgetPlugin::toolTip() const
{
    return QString();
}

QString AudioDeviceWidgetPlugin::whatsThis() const
{
    return QString();
}

bool AudioDeviceWidgetPlugin::isContainer() const
{
    return false;
}

QString AudioDeviceWidgetPlugin::domXml() const
{
    return "<ui language=\"c++\">\n"
           " <widget class=\"AudioDeviceWidget\" name=\"audioDevice\">\n"
           "  <property name=\"geometry\">\n"
           "   <rect>\n"
           "    <x>0</x>\n"
           "    <y>0</y>\n"
           "    <width>100</width>\n"
           "    <height>100</height>\n"
           "   </rect>\n"
           "  </property>\n"
           "  <property name=\"toolTip\">\n"
           "   <string>An audio device</string>\n"
           "  </property>\n"
           "  <property name=\"whatsThis\">\n"
           "   <string>The audio device widget visualizes an audio device with volume meter and mute buttons.</string>\n"
           "  </property>\n"
           " </widget>\n"
           "</ui>\n";
}

QString AudioDeviceWidgetPlugin::includeFile() const
{
    return QStringLiteral("audiodevicewidget.h");
}
