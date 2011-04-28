#ifndef DOWNLOADERGAMINGMONTH_H
#define DOWNLOADERGAMINGMONTH_H

#include "common.h"

class DownKhlRuGamingMonth : public DownloaderKhlRu
{
        Q_OBJECT
    public:
        DownKhlRuGamingMonth(QObject* parent = 0, const QString& siteName = "www.khl.ru") :
                DownloaderKhlRu(parent, siteName)
        {
            setInterval(-1);
        }
        virtual void run();
    protected:
       virtual  void setupUrlAndFileByDate();
       virtual  void launchDownloadingProcess();
       QFile file;
   private:
        QString getAddToUrl(const QList<MapValue> & list, int key);
};

#endif // DOWNLOADERGAMINGMONTH_H
