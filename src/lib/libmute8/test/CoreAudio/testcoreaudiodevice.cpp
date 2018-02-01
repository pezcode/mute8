#include "testcoreaudiodevice.h"

#include <impl/CoreAudio/deviceenumerator.h>
#include <impl/CoreAudio/audiodevice.h>
#include <algorithm> // copy_if
#include <stdexcept>

using namespace mute8;

void TestCoreAudioDevice::initTestCase()
{
    CoreDeviceEnumerator enumerator;
    enumerator.populate();
    if(enumerator.count() == 0)
    {
        QSKIP("No audio devices");
    }
    this->devices = enumerator.devices();
}

// CoreAudioDevice throws on nullptr argument in its constructor
void TestCoreAudioDevice::ctorThrowsOnNullPtr() const
{
    QVERIFY_EXCEPTION_THROWN(CoreAudioDevice device(nullptr), std::invalid_argument);
}

// All devices have a non-empty description, adapter, name and ID
void TestCoreAudioDevice::hasNamesAndId() const
{
    for(const auto& device : this->devices)
    {
        QVERIFY(!device->getDescription().empty());
        QVERIFY(!device->getAdapter().empty());
        QVERIFY(!device->getName().empty());
        QVERIFY(!device->getId().empty());
    }
}

// There are no duplicate IDs in the device list
void TestCoreAudioDevice::uniqueIds() const
{
    std::vector<std::shared_ptr<mute8::IAudioDevice>> uniqueDevices;

    std::unique_copy(this->devices.begin(), this->devices.end(), std::back_inserter(uniqueDevices), [](const std::shared_ptr<IAudioDevice>& dev1, const std::shared_ptr<IAudioDevice>& dev2) {
        return dev1->getId() == dev2->getId();
    });
    QVERIFY(uniqueDevices.size() == this->devices.size());
}

// Peak values are in the range [0, 1]
void TestCoreAudioDevice::peakValidRange() const
{
    for(const auto& device : this->devices)
    {
        float peak = device->getPeak();
        QVERIFY(peak >= 0.0f && peak <= 1.0f);
    }
}
