#ifndef PARSERKHLRU_H
#define PARSERKHLRU_H

#include <QObject>
#include <QDateTime>
#include <QThread>

#include "iparser.h"
#include "constants.h"

class ParserKhlRu : public IParser
{
        Q_OBJECT
    public:
        explicit ParserKhlRu(QObject* parent = 0, const QString& targetName = "www.khl.ru") : IParser(parent, targetName)
        {
        }

        virtual ~ParserKhlRu() {}
    signals:

};

#endif // PARSERKHLRU_H
