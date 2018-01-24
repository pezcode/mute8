#ifndef TESTCOREAUDIOIMPL_H
#define TESTCOREAUDIOIMPL_H

#include <QtTest/QtTest>

class TestCoreAudioImpl : public QObject
{
  Q_OBJECT
  
  private slots:

    void enumeratorEmpty() const;
    void enumeratorClear() const;
    void enumeratorDeviceCount() const;
    void enumeratorTypeCount() const;
    void enumeratorStateCount() const;
    void enumeratorType() const;
    void enumeratorState() const;

    void deviceCtorNull() const;
    void deviceHaveNameAndId() const;
    void deviceUniqueIds() const;
    void deviceVolumeActivePtr() const;

    void volumeCtorNull() const;
    void volumeRange() const;
    void volumeSetVolume() const;
    void volumeSetMute() const;
    // void volumeMuteVolumeInteraction() const;
};

#endif // TESTCOREAUDIOIMPL_H
