#ifndef RWKHLRUGAMINGDAY_TMP_H
#define RWKHLRUGAMINGDAY_TMP_H
#include <QFile>

#include "r_common.h"

class RWKhlRuGamingDay: public RWKhlRu
{
    public:
        RWKhlRuGamingDay(QObject* parent = 0, const QString& targetSite = "www.khl.ru-day") : RWKhlRu(parent, targetSite) {}
        virtual void run();

    protected:
        QString savedParsedFile;
        void setSavedParsedFilename();

    private:
        QStringList getDataFromParsedXML(QFile* source, const QString& resfname);
};

#endif // RWKHLRUGAMINGDAY_TMP_H
