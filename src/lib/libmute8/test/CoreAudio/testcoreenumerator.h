#ifndef TESTCOREENUMERATOR_H
#define TESTCOREENUMERATOR_H

#include <QtTest/QtTest>
#include <impl/CoreAudio/deviceenumerator.h>

class TestCoreEnumerator : public QObject
{
  Q_OBJECT

private:

    mute8::CoreDeviceEnumerator enumerator;
    size_t _emptyCount;

private slots:

    void initTestCase();

    void emptyCount() const;
    void clearCount() const;
    void deviceCount() const;
    void typesAddUp() const;
    void statesAddUp() const;
    void devicesReturnsCorrectType() const;
    void devicesReturnsCorrectState() const;
};

#endif // TESTCOREENUMERATOR_H
