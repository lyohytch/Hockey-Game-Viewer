#include "operationpool.h"

OperationPool::OperationPool(QObject* parent):
    QObject(parent)
{
}

IOperation* OperationPool::getOperationByName(const QString& siteName)
{
    foreach(IOperation * op, _operations)
    {
        if (op->targetSite() == siteName)
        {
            return op;
        }
    }
    return 0;
}

void OperationPool::appendOperation(IOperation* operation)
{
    _operations.append(operation);
}
