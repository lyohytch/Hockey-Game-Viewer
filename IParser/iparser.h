#ifndef IPARSER_H
#define IPARSER_H

#include "ioperation.h"

class IParser : public IOperation
{
        Q_OBJECT
        Q_PROPERTY(QString targetSite READ targetSite)
    public:
        IParser(QObject* parent = 0, const QString& siteName = 0) : IOperation(parent, siteName) {}
};

#endif // IPARSER_H
