#include <impl/CoreAudio/deviceenumerator.h>

#include <QtTest/QtTest>
#include "testcoreaudioimpl.h"

using namespace mute8;

void TestCoreAudioImpl::enumeratorEmptyCount() const
{
    CoreDeviceEnumerator enumerator;
    QVERIFY(enumerator.count() == 0);
}

void TestCoreAudioImpl::enumeratorPopulate() const
{
    CoreDeviceEnumerator enumerator;
    bool success = enumerator.populate();
    QVERIFY(success);
}

void TestCoreAudioImpl::enumeratorClear() const
{
    CoreDeviceEnumerator enumerator;
    size_t emptyCount = enumerator.count();
    enumerator.populate();
    enumerator.clear();
    QVERIFY(enumerator.count() == emptyCount);
}

void TestCoreAudioImpl::enumeratorTypeCount() const
{
    CoreDeviceEnumerator enumerator;
    enumerator.populate();
    const auto inDevices = enumerator.devices(IAudioDevice::tInput, IAudioDevice::sAny);
    const auto outDevices = enumerator.devices(IAudioDevice::tOutput, IAudioDevice::sAny);
    const auto allDevices = enumerator.devices(IAudioDevice::tAny, IAudioDevice::sAny);
    QVERIFY(inDevices.size() + outDevices.size() == allDevices.size());
}

void TestCoreAudioImpl::enumeratorStateCount() const
{
    CoreDeviceEnumerator enumerator;
    enumerator.populate();
    const auto activeDevices = enumerator.devices(IAudioDevice::tAny, IAudioDevice::sActive);
    const auto disabledDevices = enumerator.devices(IAudioDevice::tAny, IAudioDevice::sDisabled);
    const auto allDevices = enumerator.devices(IAudioDevice::tAny, IAudioDevice::sAny);
    QVERIFY(activeDevices.size() + disabledDevices.size() == allDevices.size());
}

QTEST_MAIN(TestCoreAudioImpl)
