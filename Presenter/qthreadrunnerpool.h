#ifndef QTHREADRUNNERPOOL_H
#define QTHREADRUNNERPOOL_H

#include <QObject>
#include <QThread>
#include "qthreadrunner.h"

class QThreadRunnerPool : public QObject
{
    Q_OBJECT
public:
    QThreadRunnerPool(QObject *parent = 0);
    void startAll();
    void startRunnerByName(const QString &opName);
    void appendRunner(QThreadRunner *runner);
    QThreadRunner* getRunner(const QString &opName);
private:
    QList<QThreadRunner *> _runners;
};

#endif // QTHREADRUNNERPOOL_H
