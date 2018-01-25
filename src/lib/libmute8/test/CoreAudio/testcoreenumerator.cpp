#include "testcoreenumerator.h"

using namespace mute8;

void TestCoreEnumerator::initTestCase()
{
    this->_emptyCount = this->enumerator.count();
    this->enumerator.populate();
}

// New enumerator has a device count of 0
void TestCoreEnumerator::emptyCount() const
{
    QVERIFY(this->_emptyCount == 0);
}

// Clear removes all devices
void TestCoreEnumerator::clearCount() const
{
    // temp enumerator so we don't clear the copy populated in initTestCase
    CoreDeviceEnumerator tempEnumerator;
    tempEnumerator.populate();
    tempEnumerator.clear();
    QVERIFY(tempEnumerator.count() == 0);
}

// Device count equals number of all unfiltered devices returned from devices()
void TestCoreEnumerator::deviceCount() const
{
    const std::vector<std::shared_ptr<IAudioDevice>> devices = this->enumerator.devices(IDeviceEnumerator::any, IDeviceEnumerator::any);
    QVERIFY(this->enumerator.count() == devices.size());
}

// Different types add up to unfiltered device count
void TestCoreEnumerator::typesAddUp() const
{
    const auto inputDevices = this->enumerator.devices(IAudioDevice::tInput, IDeviceEnumerator::any);
    const auto outputDevices = this->enumerator.devices(IAudioDevice::tOutput, IDeviceEnumerator::any);
    const auto allDevices = this->enumerator.devices(IDeviceEnumerator::any, IDeviceEnumerator::any);
    QVERIFY(inputDevices.size() + outputDevices.size() == allDevices.size());
}

// Different states add up to unfiltered device count
void TestCoreEnumerator::statesAddUp() const
{
    const auto activeDevices = this->enumerator.devices(IDeviceEnumerator::any, IAudioDevice::sActive);
    const auto disabledDevices = this->enumerator.devices(IDeviceEnumerator::any, IAudioDevice::sDisabled);
    const auto allDevices = this->enumerator.devices(IDeviceEnumerator::any, IDeviceEnumerator::any);
    QVERIFY(activeDevices.size() + disabledDevices.size() == allDevices.size());
}

// Filtering returns the correct device types
void TestCoreEnumerator::devicesReturnsCorrectType() const
{
    const auto inputDevices = this->enumerator.devices(IAudioDevice::tInput, IDeviceEnumerator::any);
    const auto outputDevices = this->enumerator.devices(IAudioDevice::tOutput, IDeviceEnumerator::any);
    for(const auto& device: inputDevices)
    {
        QVERIFY(device->getType() == IAudioDevice::tInput);
    }
    for(const auto& device: outputDevices)
    {
        QVERIFY(device->getType() == IAudioDevice::tOutput);
    }
}

// Filtering returns the correct device states
void TestCoreEnumerator::devicesReturnsCorrectState() const
{
    const auto activeDevices = this->enumerator.devices(IDeviceEnumerator::any, IAudioDevice::sActive);
    const auto disabledDevices = this->enumerator.devices(IDeviceEnumerator::any, IAudioDevice::sDisabled);
    for(const auto& device: activeDevices)
    {
        QVERIFY(device->getState() == IAudioDevice::sActive);
    }
    for(const auto& device: disabledDevices)
    {
        QVERIFY(device->getState() == IAudioDevice::sDisabled);
    }
}
