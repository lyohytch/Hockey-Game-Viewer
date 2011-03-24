#include "qthreadrunner.h"
#include "constants.h"

QThreadRunner::~QThreadRunner()
{
    foreach(QTimerLauncher *timer, timers)
    {
        qDebug()<<"Timer deleted";
        delete timer;
    }
    qDebug()<<"Clear timers list";
    timers.clear();
}

void QThreadRunner::run()
{
    qDebug()<<"Start new runner operation at "<<QThread::currentThreadId()<<" thread id";
    QTimerLauncher *timer =  new QTimerLauncher();
    timer->setOperation(operation());
    timer->startTimer(operation()->interval());
    timers.append(timer);
    exec();
}

void QTimerLauncher::timerEvent(QTimerEvent *event)
{
    qDebug()<< "Timer ID:" << event->timerId()<<":"<<QThread::currentThreadId();
    operation()->run();
}


