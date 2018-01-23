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
    const auto inDevices = enumerator.devices(IAudioDevice::tInput, IDeviceEnumerator::any);
    const auto outDevices = enumerator.devices(IAudioDevice::tOutput, IDeviceEnumerator::any);
    const auto allDevices = enumerator.devices(IDeviceEnumerator::any, IDeviceEnumerator::any);
    QVERIFY(inDevices.size() + outDevices.size() == allDevices.size());
}

void TestCoreAudioImpl::enumeratorStateCount() const
{
    CoreDeviceEnumerator enumerator;
    enumerator.populate();
    const auto activeDevices = enumerator.devices(IDeviceEnumerator::any, IAudioDevice::sActive);
    const auto disabledDevices = enumerator.devices(IDeviceEnumerator::any, IAudioDevice::sDisabled);
    const auto allDevices = enumerator.devices(IDeviceEnumerator::any, IDeviceEnumerator::any);
    QVERIFY(activeDevices.size() + disabledDevices.size() == allDevices.size());
}

QTEST_MAIN(TestCoreAudioImpl)
