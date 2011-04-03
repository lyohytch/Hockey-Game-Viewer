#include <QObject>

#include "qthreadrunner.h"
#include "constants.h"

//QThreadRunner
void QThreadRunner::stopExec()
{
    if (this->isRunning())
    {
        qDebug() << "Stop thread execution";
        this->quit();
    }
}

//QThreadPeriodRunner
QThreadPeriodRunner::~QThreadPeriodRunner()
{
    foreach(QTimerLauncher * timer, timers)
    {
        qDebug() << "Timer deleted";
        delete timer;
    }
    qDebug() << "Clear timers list";
    timers.clear();
}

void QThreadPeriodRunner::run()
{
    qDebug() << "Start new runner operation at " << QThread::currentThreadId() << " thread id";
    QTimerLauncher* timer =  new QTimerLauncher();
    timer->setOperation(operation());
    qDebug() << "Interval: " << operation()->interval();
    operation()->run();
    timer->startTimer(operation()->interval());
    timers.append(timer);
    exec();
}

void QTimerLauncher::timerEvent(QTimerEvent* event)
{
    qDebug() << "Timer ID:" << event->timerId() << ":" << QThread::currentThreadId();
    operation()->run();
}

//QThreadOneRunner
void QThreadOneRunner::run()
{
    qDebug() << "Start new runner operation at " << QThread::currentThreadId() << " thread id";
    connect(operation(), SIGNAL(endOperation()), this, SLOT(stopExec()), Qt::UniqueConnection);
    operation()->run();
    exec();
}
