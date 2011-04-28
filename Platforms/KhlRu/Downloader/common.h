#ifndef DOWNLOADERKHLRU_H
#define DOWNLOADERKHLRU_H

#include <QThread>
#include <QDateTime>
#include <QFile>

#include "idownloader.h"

class KhlRuReceiver : public IReceiver
{
        Q_OBJECT
    public:
        KhlRuReceiver(QNetworkAccessManager* _mgr, QFile* _file, const QString &urlForDownload);
    public slots:
        virtual void httpFinished();
        virtual void httpReadyRead();

};

class DownloaderKhlRu : public IDownloader
{
        Q_OBJECT
    public:
        explicit DownloaderKhlRu(QObject* parent = 0, const QString& siteName = "www.khl.ru") : IDownloader(parent, siteName)
        {
        }
        virtual ~DownloaderKhlRu() {}
        void executeDownloadingProcess();
    protected:


};

#endif // DOWNLOADERKHLRU_H
