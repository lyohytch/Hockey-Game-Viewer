#ifndef IPARSER_H
#define IPARSER_H

#include "ioperation.h"

class IParser : public IOperation
{
        Q_OBJECT
    public:
        IParser(QObject* parent = 0, const QString& siteName = 0) : IOperation(parent, siteName) {}
    signals:
        void parsedGamingMonth();
};

#endif // IPARSER_H
