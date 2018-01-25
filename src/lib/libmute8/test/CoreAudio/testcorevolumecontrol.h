#ifndef TESTCOREVOLUMECONTROL_H
#define TESTCOREVOLUMECONTROL_H

#include <QtTest/QtTest>

#include <iaudiodevice.h>
#include <vector>
#include <memory>

class TestCoreVolumeControl : public QObject
{
  Q_OBJECT

private:

    static bool compareVolumes(float fl1, float fl2);

    std::vector<std::shared_ptr<mute8::IAudioDevice>> devices;

private slots:

    void initTestCase();

    void ctorThrowsOnNullPtr() const;
    void outputValidRange() const;
    void inputInvalidRangeThrows() const;
    void setVolumePersistance() const;
    void setMutePersistance() const;
    void muteAndVolumeIndependent() const;
};

#endif // TESTCOREVOLUMECONTROL_H
