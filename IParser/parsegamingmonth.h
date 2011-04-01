#ifndef PARSEGAMINGMONTH_H
#define PARSEGAMINGMONTH_H

#include "parserkhlru.h"

class ParseKhlRuGamingMonth : public ParserKhlRu
{
    Q_OBJECT
public:
    explicit ParseKhlRuGamingMonth(QObject *parent = 0, const QString& targetName = "www.khl.ru") : ParserKhlRu(parent, targetName)
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

#endif // PARSEGAMINGMONTH_H
