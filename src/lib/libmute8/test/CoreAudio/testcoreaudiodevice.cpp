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
    this->devices = enumerator.devices(IDeviceEnumerator::any, IDeviceEnumerator::any);
}

// CoreAudioDevice throws on nullptr argument in its constructor
void TestCoreAudioDevice::ctorThrowsOnNullPtr() const
{
    QVERIFY_EXCEPTION_THROWN(CoreAudioDevice device(nullptr), std::invalid_argument);
}

// All devices have a non-empty name and ID
void TestCoreAudioDevice::hasNameAndId() const
{
    for(const auto& device : this->devices)
    {
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
