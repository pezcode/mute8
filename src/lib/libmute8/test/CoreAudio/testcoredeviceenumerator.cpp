#include "testcoredeviceenumerator.h"

using namespace mute8;

void TestCoreDeviceEnumerator::initTestCase()
{
    this->initialCount = this->enumerator.count();
    this->initialDeviceCount = this->enumerator.devices().size();
    this->enumerator.populate();

    this->devices = this->enumerator.devices();
    this->inputDevices = this->enumerator.devices(IAudioDevice::tInput);
    this->outputDevices = this->enumerator.devices(IAudioDevice::tOutput);
    this->activeDevices = this->enumerator.devices(IAudioDevice::sActive);
    this->disabledDevices = this->enumerator.devices(IAudioDevice::sDisabled);
}

// New enumerator has a device count of 0
void TestCoreDeviceEnumerator::emptyCount() const
{
    QVERIFY(this->initialCount == 0);
    QVERIFY(this->initialDeviceCount == 0);
}

// Clear removes all devices
void TestCoreDeviceEnumerator::clearCount() const
{
    // temp enumerator so we don't clear the copy populated in initTestCase
    CoreDeviceEnumerator tempEnumerator;
    tempEnumerator.populate();
    tempEnumerator.clear();
    QVERIFY(tempEnumerator.count() == 0);
    const auto devices = tempEnumerator.devices();
    QVERIFY(devices.size() == 0);
}

// Device count equals number of all unfiltered devices returned from devices()
void TestCoreDeviceEnumerator::deviceCount() const
{
    QVERIFY(this->enumerator.count() == this->devices.size());
}

// Different types add up to unfiltered device count
void TestCoreDeviceEnumerator::typesAddUp() const
{
    QVERIFY(this->inputDevices.size() + this->outputDevices.size() == this->devices.size());
}

// Different states add up to unfiltered device count
void TestCoreDeviceEnumerator::statesAddUp() const
{
    QVERIFY(this->activeDevices.size() + this->disabledDevices.size() == this->devices.size());
}

// Filtering returns the correct device types
void TestCoreDeviceEnumerator::devicesReturnsCorrectType() const
{
    for(const auto& device: this->inputDevices)
    {
        QVERIFY(device->getType() == IAudioDevice::tInput);
    }
    for(const auto& device: this->outputDevices)
    {
        QVERIFY(device->getType() == IAudioDevice::tOutput);
    }
}

// Filtering returns the correct device states
void TestCoreDeviceEnumerator::devicesReturnsCorrectState() const
{
    for(const auto& device: this->activeDevices)
    {
        QVERIFY(device->getState() == IAudioDevice::sActive);
    }
    for(const auto& device: this->disabledDevices)
    {
        QVERIFY(device->getState() == IAudioDevice::sDisabled);
    }
}
