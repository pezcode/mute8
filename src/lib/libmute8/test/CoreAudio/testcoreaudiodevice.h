#ifndef TESTCOREAUDIODEVICE_H
#define TESTCOREAUDIODEVICE_H

#include <QtTest/QtTest>
#include <iaudiodevice.h>
#include <vector>
#include <memory>

class TestCoreAudioDevice : public QObject
{
    Q_OBJECT

private:

    std::vector<std::shared_ptr<mute8::IAudioDevice>> devices;
  
private slots:

    void initTestCase();

    void ctorThrowsOnNullPtr() const;
    void hasNameAndId() const;
    void uniqueIds() const;
};

#endif // TESTCOREAUDIODEVICE_H
