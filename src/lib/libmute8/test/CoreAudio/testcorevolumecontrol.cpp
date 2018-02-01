#include "testcorevolumecontrol.h"
#include <impl/CoreAudio/deviceenumerator.h>
#include <impl/CoreAudio/volumecontrol.h>
#include <cstdlib> // abs

using namespace mute8;

bool TestCoreVolumeControl::compareVolumes(float fl1, float fl2)
{
    // allow volume difference of 2%
    constexpr float VOL_EPSILON = 0.02f;

    return std::abs(fl1 - fl2) < VOL_EPSILON;
}

void TestCoreVolumeControl::initTestCase()
{
    CoreDeviceEnumerator enumerator;
    enumerator.populate();
    if(enumerator.count() == 0)
    {
        QSKIP("No audio devices");
    }

    this->devices = enumerator.devices();
}

/*
// Active devices export a VolumeControl
void TestCoreVolumeControl::deviceVolumeActivePtr() const
{
    for(const auto& device : this->devices)
    {
        const std::shared_ptr<IVolumeControl> volume = device->getVolumeControl();
        if(device->getState() == IAudioDevice::sActive)
        {
            QVERIFY(volume != nullptr);
        }
    }
}
*/

// CoreVolumeControl throws on nullptr argument in its constructor
void TestCoreVolumeControl::ctorThrowsOnNullPtr() const
{
    QVERIFY_EXCEPTION_THROWN(CoreVolumeControl volume(nullptr), std::invalid_argument);
}

// Volume is in the range [0, 1]
void TestCoreVolumeControl::outputValidRange() const
{
    for(const auto& device : this->devices)
    {
        auto volumeControl = device->getVolumeControl();
        if(volumeControl)
        {
            float volume = volumeControl->getVolume();
            QVERIFY(volume >= 0.0f && volume <= 1.0f);
        }
    }
}

// Setting volume outside the range [0, 1] throws an exception
void TestCoreVolumeControl::inputInvalidRangeThrows() const
{
    for(const auto& device : this->devices)
    {
        auto volumeControl = device->getVolumeControl();
        if(volumeControl)
        {
            float oldVolume = volumeControl->getVolume();
            QVERIFY_EXCEPTION_THROWN(volumeControl->setVolume(-0.5f), std::invalid_argument);
            QVERIFY_EXCEPTION_THROWN(volumeControl->setVolume(1.5f), std::invalid_argument);
            // just in case
            volumeControl->setVolume(oldVolume);
        }
    }
}

// Volume set with setVolume is persistent
void TestCoreVolumeControl::setVolumePersistance() const
{
    for(const auto& device : this->devices)
    {
        auto volumeControl = device->getVolumeControl();
        if(volumeControl)
        {
            float oldVolume = volumeControl->getVolume();
            float newVolume = 1.0f - oldVolume;
            volumeControl->setVolume(newVolume);
            float testVolume = volumeControl->getVolume();
            volumeControl->setVolume(oldVolume);
            QVERIFY(this->compareVolumes(testVolume, newVolume));
        }
    }
}

// Mute state set with setMute is persistent
void TestCoreVolumeControl::setMutePersistance() const
{
    for(const auto& device : this->devices)
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

// Mute state and volume are independent of each other
void TestCoreVolumeControl::muteAndVolumeIndependent() const
{
    for(const auto& device : this->devices)
    {
        auto volumeControl = device->getVolumeControl();
        if(volumeControl)
        {
            float oldVolume = volumeControl->getVolume();
            bool oldMute = volumeControl->getMute();

            volumeControl->setVolume(0.0f);
            bool testMute0 = volumeControl->getMute();
            volumeControl->setVolume(1.0f);
            bool testMute1 = volumeControl->getMute();
            volumeControl->setVolume(oldVolume);

            volumeControl->setMute(true);
            float testVolume0 = volumeControl->getVolume();
            volumeControl->setMute(false);
            float testVolume1 = volumeControl->getVolume();
            volumeControl->setMute(oldMute);

            QVERIFY(testMute0 == oldMute);
            QVERIFY(testMute1 == oldMute);
            QVERIFY(this->compareVolumes(testVolume0, oldVolume));
            QVERIFY(this->compareVolumes(testVolume1, oldVolume));
        }
    }
}
