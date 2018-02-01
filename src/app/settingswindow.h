#ifndef SETTINGSWINDOW_H
#define SETTINGSWINDOW_H

#include <QMainWindow>
#include <iaudiodevice.h>
#include <audiodevicewidget.h>
// TODO abstract this away into a factory function (global Mute8 object?)
#include <impl/CoreAudio/deviceenumerator.h>
#include <QList>

namespace Ui {
class SettingsWindow;
}

class SettingsWindow : public QMainWindow
{
    Q_OBJECT

public:

    explicit SettingsWindow(QWidget *parent = 0);
    ~SettingsWindow();

private:

    Ui::SettingsWindow *ui;

    //std::shared_ptr<mute8::IAudioDevice> defaultDevice;

    mute8::IDeviceEnumerator::DeviceList inDevices;
    mute8::IDeviceEnumerator::DeviceList outDevices;
    QList<AudioDeviceWidget*> deviceWidgets;

    QTimer *peakTimer;
};

#endif // SETTINGSWINDOW_H
