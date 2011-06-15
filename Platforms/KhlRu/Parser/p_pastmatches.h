#ifndef PARSEGAMINGMONTH_H
#define PARSEGAMINGMONTH_H

#include "p_common.h"

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
    virtual void setFilenameForParsing();
    virtual void finishTask();
};

#endif // PARSEGAMINGMONTH_H
