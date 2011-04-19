#ifndef DOWNLOADERKHLRUGAMINGDAY_H
#define DOWNLOADERKHLRUGAMINGDAY_H

#include "common.h"

class KhlRuGamingDayReceiver : public IReceiver
{
        Q_OBJECT
    public:
        KhlRuGamingDayReceiver(QNetworkAccessManager* _mgr, QFile* _file, const QString &urlForDownload);
    public slots:
        virtual void httpFinished();
        virtual void httpReadyRead();

};

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
