#ifndef DOWNLOADERGAMINGMONTH_H
#define DOWNLOADERGAMINGMONTH_H

#include "downloaderkhlru.h"
#include "constants_downloader.h"

class KhlRuGamingMonthReceiver : public IReceiver
{
        Q_OBJECT
    public:
        KhlRuGamingMonthReceiver(QNetworkAccessManager* _mgr, QNetworkReply* _reply, QFile* _file) : IReceiver(_mgr, _reply, _file)
        {
        }
    public slots:
      virtual void httpFinished();
      virtual void httpReadyRead();

};

class DownKhlRuGamingMonth : public DownloaderKhlRu
{
        Q_OBJECT
    public:
        DownKhlRuGamingMonth(QObject* parent = 0, const QString& siteName = "www.khl.ru") : DownloaderKhlRu(parent, siteName)
        {
            setInterval(200000);
        }
        virtual void run();

    protected:
        void setupUrlAndFileByDate();
        void setupNetManager();
        void launchReceiver();
        QString getAddToUrl(const QList<MapValue> & list, int key);
        QString url;
        QString fname;
        QString newDir;
        QString currDir;
};

#endif // DOWNLOADERGAMINGMONTH_H
