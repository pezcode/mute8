#include "CoreAudio/testcoreenumerator.h"
#include "CoreAudio/testcoreaudiodevice.h"
#include "CoreAudio/testcorevolumecontrol.h"

int main(int argc, char *argv[])
{
    //QTEST_SET_MAIN_SOURCE_PATH
    //QCoreApplication app(argc, argv);

    TestCoreEnumerator coreEnumerator;
    TestCoreAudioDevice coreAudioDevice;
    TestCoreVolumeControl coreVolumeControl;

    QTest::qExec(&coreEnumerator, argc, argv);
    QTest::qExec(&coreAudioDevice, argc, argv);
    QTest::qExec(&coreVolumeControl, argc, argv);
}
