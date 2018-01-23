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

    for(const auto device: enumerator.devices(mute8::IAudioDevice::tInput, mute8::IAudioDevice::sActive))
    {
        ui->listWidget->addItem(QString::fromStdString(device->getName()));
    }
}

SettingsWindow::~SettingsWindow()
{
    delete ui;
}
