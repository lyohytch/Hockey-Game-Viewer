#ifndef IRWDATA_H
#define IRWDATA_H

#include "ioperation.h"

class IRWData : public IOperation
{
        Q_OBJECT
    public:
        explicit IRWData(QObject* parent = 0, const QString& typeName = 0): IOperation(parent, typeName) {}
    signals:
        void FileNotExistToReading();
    public slots:

};

#endif // IRWDATA_H
