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
        ~QThreadRunner();
        void run();
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
        QList<QTimerLauncher *> timers;
};
#endif // QTHREADRUNNER_H
