#include "qthreadrunner.h"
#include "qthreadrunnerpool.h"
#include "constants.h"

QThreadRunnerPool::QThreadRunnerPool(QObject *parent) :
    QObject(parent)
{
}

void QThreadRunnerPool::startAll()
{
    foreach(QThreadRunner *runner, _runners)
    {
        runner->start();
    }
}

void QThreadRunnerPool::startRunnerByName(const QString &opName)
{
    getRunner(opName)->start();
}

void QThreadRunnerPool::appendRunner(QThreadRunner *runner)
{
    _runners.append(runner);
}

QThreadRunner* QThreadRunnerPool::getRunner(const QString &opName)
{
    foreach(QThreadRunner * runner, _runners)
    {
        if (runner->operationName() == opName )
        {
            return runner;
        }
    }

    return 0;
}
