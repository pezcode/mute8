#ifndef TESTCOREAUDIODEVICE_H
#define TESTCOREAUDIODEVICE_H

#include <QtTest/QtTest>
#include <ideviceenumerator.h>
#include <iaudiodevice.h>
#include <vector>
#include <memory>

class TestCoreAudioDevice : public QObject
{
    Q_OBJECT

private:

    mute8::IDeviceEnumerator::DeviceList devices;
  
private slots:

    void initTestCase();

    void ctorThrowsOnNullPtr() const;
    void hasNamesAndId() const;
    void uniqueIds() const;
    void peakValidRange() const;
};

#endif // TESTCOREAUDIODEVICE_H
