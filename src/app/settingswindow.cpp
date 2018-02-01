#include "settingswindow.h"
#include "ui_settingswindow.h"

#include <QTimer>

SettingsWindow::SettingsWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::SettingsWindow),
    peakTimer(new QTimer(this))
{
    ui->setupUi(this);

    mute8::CoreDeviceEnumerator enumerator;
    enumerator.populate();

    inDevices = enumerator.devices(mute8::IAudioDevice::tInput, mute8::IAudioDevice::sActive);
    outDevices = enumerator.devices(mute8::IAudioDevice::tOutput, mute8::IAudioDevice::sActive);

    QVBoxLayout* inputLayout = qobject_cast<QVBoxLayout*>(ui->tab_input->layout());
    Q_ASSERT(inputLayout != nullptr);
    for(const auto device: inDevices)
    {
        AudioDeviceWidget* widget = new AudioDeviceWidget(this);
        deviceWidgets += widget;
        ui->tab_input->layout()->addWidget(widget);
        widget->setDeviceName(QString::fromStdString(device->getDescription()));
        widget->setAdapterName(QString::fromStdString(device->getAdapter()));
        connect(peakTimer, &QTimer::timeout, [widget, device]() {
            widget->peakChanged(device->getPeak());
        });
    }
    inputLayout->insertStretch(-1);

    QVBoxLayout* outputLayout = qobject_cast<QVBoxLayout*>(ui->tab_output->layout());
    Q_ASSERT(outputLayout != nullptr);
    for(const auto device: outDevices)
    {
        AudioDeviceWidget* widget = new AudioDeviceWidget(this);
        deviceWidgets += widget;
        ui->tab_output->layout()->addWidget(widget);
        widget->setDeviceName(QString::fromStdString(device->getDescription()));
        widget->setAdapterName(QString::fromStdString(device->getAdapter()));
        connect(peakTimer, &QTimer::timeout, [widget, device]() {
            widget->peakChanged(device->getPeak());
        });
    }
    outputLayout->insertStretch(-1);

    peakTimer->start(100);
}

SettingsWindow::~SettingsWindow()
{
    delete ui;
}
