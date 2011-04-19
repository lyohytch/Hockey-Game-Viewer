#ifndef OPERATIONPOOL_H
#define OPERATIONPOOL_H

#include "ioperation.h"

class OperationPool : public QObject
{
        Q_OBJECT
    public:
        explicit OperationPool(QObject* parent = 0);
        IOperation* getOperationByName(const QString& siteName);
        void appendOperation(IOperation* operation);

    signals:

    public slots:

    private:
        QList<IOperation*> _operations;

};


#endif // OPERATIONPOOL_H
