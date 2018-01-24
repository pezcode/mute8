#include <impl/CoreAudio/deviceenumerator.h>

#include <QtTest/QtTest>
#include "testcoreaudioimpl.h"

#include <impl/CoreAudio/audiodevice.h>
#include <impl/CoreAudio/volumecontrol.h>
#include <algorithm>
#include <stdexcept>

using namespace mute8;

// New enumerator has a device count of 0
void TestCoreAudioImpl::enumeratorEmpty() const
{
    CoreDeviceEnumerator enumerator;
    QVERIFY(enumerator.count() == 0);
}

// Clear removes all devices
void TestCoreAudioImpl::enumeratorClear() const
{
    CoreDeviceEnumerator enumerator;
    size_t emptyCount = enumerator.count();
    enumerator.populate();
    enumerator.clear();
    QVERIFY(enumerator.count() == emptyCount);
}

// Device count equals number of all unfiltered devices returned from devices()
void TestCoreAudioImpl::enumeratorDeviceCount() const
{
    CoreDeviceEnumerator enumerator;
    const std::vector<std::shared_ptr<IAudioDevice>> devices = enumerator.devices(IDeviceEnumerator::any, IDeviceEnumerator::any);
    QVERIFY(enumerator.count() == devices.size());
}

// Different types add up to unfiltered device count
void TestCoreAudioImpl::enumeratorTypeCount() const
{
    CoreDeviceEnumerator enumerator;
    enumerator.populate();
    const auto inputDevices = enumerator.devices(IAudioDevice::tInput, IDeviceEnumerator::any);
    const auto outputDevices = enumerator.devices(IAudioDevice::tOutput, IDeviceEnumerator::any);
    const auto allDevices = enumerator.devices(IDeviceEnumerator::any, IDeviceEnumerator::any);
    QVERIFY(inputDevices.size() + outputDevices.size() == allDevices.size());
}

// Different states add up to unfiltered device count
void TestCoreAudioImpl::enumeratorStateCount() const
{
    CoreDeviceEnumerator enumerator;
    enumerator.populate();
    const auto activeDevices = enumerator.devices(IDeviceEnumerator::any, IAudioDevice::sActive);
    const auto disabledDevices = enumerator.devices(IDeviceEnumerator::any, IAudioDevice::sDisabled);
    const auto allDevices = enumerator.devices(IDeviceEnumerator::any, IDeviceEnumerator::any);
    QVERIFY(activeDevices.size() + disabledDevices.size() == allDevices.size());
}

// Filtering returns the correct device types
void TestCoreAudioImpl::enumeratorType() const
{
    CoreDeviceEnumerator enumerator;
    enumerator.populate();

    const auto inputDevices = enumerator.devices(IAudioDevice::tInput, IDeviceEnumerator::any);
    for(const auto& device: inputDevices)
    {
        QVERIFY(device->getType() == IAudioDevice::tInput);
    }

    const auto outputDevices = enumerator.devices(IAudioDevice::tOutput, IDeviceEnumerator::any);
    for(const auto& device: outputDevices)
    {
        QVERIFY(device->getType() == IAudioDevice::tOutput);
    }
}

// Filtering returns the correct device states
void TestCoreAudioImpl::enumeratorState() const
{
    CoreDeviceEnumerator enumerator;
    enumerator.populate();

    const auto activeDevices = enumerator.devices(IDeviceEnumerator::any, IAudioDevice::sActive);
    for(const auto& device: activeDevices)
    {
        QVERIFY(device->getState() == IAudioDevice::sActive);
    }

    const auto disabledDevices = enumerator.devices(IDeviceEnumerator::any, IAudioDevice::sDisabled);
    for(const auto& device: disabledDevices)
    {
        QVERIFY(device->getState() == IAudioDevice::sDisabled);
    }
}

// CoreAudioDevice throws on nullptr argument in its constructor
void TestCoreAudioImpl::deviceCtorNull() const
{
    QVERIFY_EXCEPTION_THROWN(CoreAudioDevice device(nullptr), std::invalid_argument);
}

// All devices have a non-empty name and ID
void TestCoreAudioImpl::deviceHaveNameAndId() const
{
    CoreDeviceEnumerator enumerator;
    enumerator.populate();
    if(enumerator.count() == 0)
    {
        QSKIP("No audio devices");
    }

    const auto devices = enumerator.devices(IDeviceEnumerator::any, IDeviceEnumerator::any);
    for(const auto& device: devices)
    {
        QVERIFY(!device->getName().empty());
        QVERIFY(!device->getId().empty());
    }
}

// There are no duplicate IDs in the device list
void TestCoreAudioImpl::deviceUniqueIds() const
{
    CoreDeviceEnumerator enumerator;
    enumerator.populate();
    if(enumerator.count() == 0)
    {
        QSKIP("No audio devices");
    }

    auto devices = enumerator.devices(IDeviceEnumerator::any, IDeviceEnumerator::any);
    std::unique(devices.begin(), devices.end(), [](const std::shared_ptr<IAudioDevice>& dev1, const std::shared_ptr<IAudioDevice>& dev2) {
        return dev1->getId() == dev2->getId();
    });
    QVERIFY(devices.size() == enumerator.count());
}

// Active devices export a VolumeControl
void TestCoreAudioImpl::deviceVolumeActivePtr() const
{
    CoreDeviceEnumerator enumerator;
    enumerator.populate();
    if(enumerator.count() == 0)
    {
        QSKIP("No audio devices");
    }

    const auto devices = enumerator.devices(IDeviceEnumerator::any, IDeviceEnumerator::any);
    for(const auto& device: devices)
    {
        const std::shared_ptr<IVolumeControl> volume = device->getVolumeControl();
        if(device->getState() == IAudioDevice::sActive)
        {
            QVERIFY(volume != nullptr);
        }
    }
}

// CoreVolumeControl throws on nullptr argument in its constructor
void TestCoreAudioImpl::volumeCtorNull() const
{
    QVERIFY_EXCEPTION_THROWN(CoreVolumeControl volume(nullptr), std::invalid_argument);
}

// Volume values are in the range [0, 1]
void TestCoreAudioImpl::volumeRange() const
{
    CoreDeviceEnumerator enumerator;
    enumerator.populate();
    if(enumerator.count() == 0)
    {
        QSKIP("No audio devices");
    }

    const auto devices = enumerator.devices(IDeviceEnumerator::any, IDeviceEnumerator::any);
    for(const auto& device: devices)
    {
        auto volumeControl = device->getVolumeControl();
        if(volumeControl)
        {
            float volume = volumeControl->getVolume();
            QVERIFY(volume >= 0.0f && volume <= 1.0f);
        }
    }
}

// Volume set with setVolume is persistent
void TestCoreAudioImpl::volumeSetVolume() const
{
    CoreDeviceEnumerator enumerator;
    enumerator.populate();
    if(enumerator.count() == 0)
    {
        QSKIP("No audio devices");
    }

    const auto devices = enumerator.devices(IDeviceEnumerator::any, IDeviceEnumerator::any);
    for(const auto& device: devices)
    {
        auto volumeControl = device->getVolumeControl();
        if(volumeControl)
        {
            float oldVolume = volumeControl->getVolume();
            float newVolume = 1.0f - oldVolume;
            volumeControl->setVolume(newVolume);
            float testVolume = volumeControl->getVolume();
            volumeControl->setVolume(oldVolume);
            // In the case of comparing floats and doubles, qFuzzyCompare() is used for comparing.
            // This means that comparing to 0 will likely fail. One solution to this is to compare to 1, and add 1 to the produced output.
            QCOMPARE(testVolume + 1.0f, newVolume + 1.0f);
        }
    }
}

// Mute state set with setMute is persistent
void TestCoreAudioImpl::volumeSetMute() const
{
    CoreDeviceEnumerator enumerator;
    enumerator.populate();
    if(enumerator.count() == 0)
    {
        QSKIP("No audio devices");
    }

    const auto devices = enumerator.devices(IDeviceEnumerator::any, IDeviceEnumerator::any);
    for(const auto& device: devices)
    {
        auto volumeControl = device->getVolumeControl();
        if(volumeControl)
        {
            bool oldMute = volumeControl->getMute();
            bool newMute = !oldMute;
            volumeControl->setMute(newMute);
            bool testMute = volumeControl->getMute();
            volumeControl->setMute(oldMute);
            QVERIFY(testMute == newMute);
        }
    }
}

// Mute state and volume affect each other?
// !! Does not hold true, mute state is independent of volume
/*
void TestCoreAudioImpl::volumeMuteVolumeInteraction() const
{
    CoreDeviceEnumerator enumerator;
    enumerator.populate();
    if(enumerator.count() == 0)
    {
        QSKIP("No audio devices");
    }

    const auto devices = enumerator.devices(IDeviceEnumerator::any, IDeviceEnumerator::any);
    for(const auto& device: devices)
    {
        auto volumeControl = device->getVolumeControl();
        if(volumeControl)
        {
            float oldVolume = volumeControl->getVolume();
            volumeControl->setVolume(0.0f);
            bool testMute = volumeControl->getMute();
            volumeControl->setVolume(oldVolume);

            bool oldMute = volumeControl->getMute();
            volumeControl->setMute(true);
            float testVolume = volumeControl->getVolume();
            volumeControl->setMute(oldMute);

            QVERIFY(testMute == true);
            QCOMPARE(testVolume + 1.0f, 1.0f);
        }
    }
}
*/

QTEST_MAIN(TestCoreAudioImpl)
