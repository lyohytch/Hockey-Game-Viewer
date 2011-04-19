#ifndef PARSERKHLRUGAMINGDAY_H
#define PARSERKHLRUGAMINGDAY_H

#include "common.h"

class ParserKhlRuGamingDay : public ParserKhlRu
{
    Q_OBJECT
public:
    explicit ParserKhlRuGamingDay(QObject *parent = 0, const QString& targetName = "www.khl.ru-day") : ParserKhlRu(parent, targetName)
    {
        setInterval(-1);
    }
    virtual void run();

protected:
    QString savedFilename;

    QString parsedFilename;
    QString parsedDir;

    void setFilenameForParsing();

};

#endif // PARSERKHLRUGAMINGDAY_H
