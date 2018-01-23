#ifndef TESTCOREAUDIOIMPL_H
#define TESTCOREAUDIOIMPL_H

#include <QtTest/QtTest>

class TestCoreAudioImpl : public QObject
{
  Q_OBJECT
  
  private slots:

    void enumeratorEmptyCount() const;
    void enumeratorPopulate() const;
    void enumeratorClear() const;
    void enumeratorTypeCount() const;
    void enumeratorStateCount() const;
};

#endif // TESTCOREAUDIOIMPL_H
