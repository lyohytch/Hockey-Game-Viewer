#ifndef DOWNLOADERKHLRUGAMINGDAY_H
#define DOWNLOADERKHLRUGAMINGDAY_H

#include "d_common.h"

class DownKhlRuGamingDay : public DownloaderKhlRu
{
    Q_OBJECT
public:
    explicit DownKhlRuGamingDay(QObject* parent = 0, const QString& siteName = "www.khl.ru-day") :
            DownloaderKhlRu(parent, siteName)
    {
        setInterval(10000);
    }
    virtual void run();
protected:
   virtual  void setupUrlAndFileByDate();
   virtual  void launchDownloadingProcess();
   QFile file;

private slots:
   void finishDownload(int);
};

#endif // DOWNLOADERKHLRUGAMINGDAY_H
