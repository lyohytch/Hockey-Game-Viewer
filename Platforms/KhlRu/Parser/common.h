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
    protected:
        QString savedFilename;
        QString parsedFilename;
        QString parsedDir;
        virtual void setFilenameForParsing() = 0;
        void parseDownloadedFile(const QString& parseFPath);
        void executeParsingProcess(const QString& parseFPath);
        virtual void finishTask();
};

#endif // PARSERKHLRU_H
