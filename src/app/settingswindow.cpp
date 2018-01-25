#include "settingswindow.h"
#include "ui_settingswindow.h"

#include <impl/CoreAudio/deviceenumerator.h>

SettingsWindow::SettingsWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::SettingsWindow)
{
    ui->setupUi(this);

    mute8::CoreDeviceEnumerator enumerator;
    enumerator.populate();

    for(const auto device: enumerator.devices(mute8::CoreDeviceEnumerator::any, mute8::CoreDeviceEnumerator::any))
    {
        QString type = device->getType() == mute8::IAudioDevice::tOutput ? "[OUT]" : "[IN]";
        QString state = device->getState() == mute8::IAudioDevice::sActive ? "[A]" : "[D]";
        QString volume = device->getVolumeControl() != nullptr ? "[V]" : "";
        QString name = QString::fromStdString(device->getName());
        ui->listWidget->addItem(type + state + volume + " " + name);
    }
}

SettingsWindow::~SettingsWindow()
{
    delete ui;
}
