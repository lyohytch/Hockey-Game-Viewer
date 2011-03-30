#include "qthreadrunner.h"
#include "qthreadrunnerpool.h"
#include "constants.h"

QThreadRunnerPool::QThreadRunnerPool(QObject* parent) :
    QObject(parent)
{
}

void QThreadRunnerPool::startAll()
{
    foreach(QThreadRunner * runner, _runners)
    {
        if (!runner->isRunning())
        {
            runner->start();
        }
    }
}

void QThreadRunnerPool::startRunnerByName(const QString& opName)
{
    QThreadRunner* runner = getRunner(opName);
    if (!runner->isRunning())
    {
        runner->start();
    }
}

void QThreadRunnerPool::appendRunner(QThreadRunner* runner)
{
    _runners.append(runner);
}

QThreadRunner* QThreadRunnerPool::getRunner(const QString& opName)
{
    foreach(QThreadRunner * runner, _runners)
    {
        if (runner->operationName() == opName)
        {
            return runner;
        }
    }

    return 0;
}
