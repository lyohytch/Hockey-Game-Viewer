#ifndef QTHREADRUNNER_H
#define QTHREADRUNNER_H

#include <QThread>
#include <QTimerEvent>
#include "ioperation.h"

class QTimerLauncher: public QObject
{
        Q_OBJECT
        Q_PROPERTY(IOperation* operation READ operation WRITE setOperation)
    public:
        QTimerLauncher(QObject* parent = 0) : QObject(parent) {}
        IOperation* operation()
        {
            return _operation;
        }

    protected:
        void timerEvent(QTimerEvent* event);
    public slots:
        void setOperation(IOperation* copyOperation)
        {
            _operation = copyOperation;
        }
    private:
        IOperation* _operation;
};


class QThreadRunner : public QThread
{
        Q_OBJECT
        Q_PROPERTY(IOperation* operation READ operation)
        Q_PROPERTY(QString operationName READ operationName)
    public:
        QThreadRunner(const QString& copyOperationName, IOperation* copyOperation)
        {
            _operationName = copyOperationName;
            _operation = copyOperation;
        }
        virtual ~QThreadRunner() {}
        virtual void run() = 0;
        IOperation* operation() const
        {
            return _operation;
        }
        QString operationName() const
        {
            return _operationName;
        }
    public slots:

    private:
        IOperation* _operation;
        QString _operationName;


};

class QThreadPeriodRunner:public QThreadRunner
{
    Q_OBJECT
public:
    QThreadPeriodRunner(const QString& copyOperationName, IOperation* copyOperation): QThreadRunner(copyOperationName, copyOperation) {}
    virtual ~QThreadPeriodRunner();
    virtual void run();
    void stopExec();
private:
    QList<QTimerLauncher *> timers;
};

class QThreadOneRunner:public QThreadRunner
{
    Q_OBJECT
public:
    QThreadOneRunner(const QString& copyOperationName, IOperation* copyOperation): QThreadRunner(copyOperationName, copyOperation) {}
    virtual ~QThreadOneRunner() {}
    virtual void run();
};

#endif // QTHREADRUNNER_H
