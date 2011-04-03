#ifndef RWKHLRUGAMINGDAY_H
#define RWKHLRUGAMINGDAY_H
#include "rwkhlru.h"
class RWKhlRuGamingDay:public RWKhlRu
{
public:
    RWKhlRuGamingDay(QObject *parent = 0, const QString &targetSite = "www.khl.ru") :RWKhlRu(parent, targetSite) {}
    virtual void run();

protected:
    QString savedParsedFile;
    void setSavedParsedFilename();
};

#endif // RWKHLRUGAMINGDAY_H
