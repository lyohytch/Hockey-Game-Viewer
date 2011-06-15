#ifndef RWKHLRUGAMINGDAY_H
#define RWKHLRUGAMINGDAY_H
#include <QFile>

#include "r_common.h"
#include "constants_downloader.h"
class RWKhlRuGamingMonth: public RWKhlRu
{
    public:
        RWKhlRuGamingMonth(QObject* parent = 0, const QString& targetSite = "www.khl.ru") : RWKhlRu(parent, targetSite) {}
        virtual void run();

    protected:
        QString savedParsedFile;
        void setSavedParsedFilename();

    private:
        QStringList getDataFromParsedXML(QFile* source, const QString& resfname);
};

#endif // RWKHLRUGAMINGDAY_H
