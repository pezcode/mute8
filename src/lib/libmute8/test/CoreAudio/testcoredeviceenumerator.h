#ifndef TESTCOREDEVICEENUMERATOR_H
#define TESTCOREDEVICEENUMERATOR_H

#include <QtTest/QtTest>
#include <impl/CoreAudio/deviceenumerator.h>

class TestCoreDeviceEnumerator : public QObject
{
  Q_OBJECT

private:

    mute8::CoreDeviceEnumerator enumerator;
    size_t initialCount, initialDeviceCount;
    mute8::IDeviceEnumerator::DeviceList devices, inputDevices, outputDevices, activeDevices, disabledDevices;

private slots:

    void initTestCase();

    void emptyCount() const;
    void clearCount() const;
    void deviceCount() const;
    void typesAddUp() const;
    void statesAddUp() const;
    void devicesReturnsCorrectType() const;
    void devicesReturnsCorrectState() const;
};

#endif // TESTCOREDEVICEENUMERATOR_H
