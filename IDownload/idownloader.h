#ifndef IDOWNLOADER_H
#define IDOWNLOADER_H

#include <QDate>
#include <QFile>
#include <QtNetwork/QNetworkProxy>
#include <QtNetwork/QNetworkAccessManager>
#include <QtNetwork/QNetworkReply>
#include <QtNetwork/QNetworkRequest>

#include "ioperation.h"
#include "constants_downloader.h"

class IReceiver: public QObject
{
        Q_OBJECT
    public:
        IReceiver(QNetworkAccessManager* _mgr, QFile* _file):
            mgr(_mgr), file(_file) {}
    signals:
        void finished(int);
    public slots:
        virtual void httpFinished() = 0;
        virtual void httpReadyRead() = 0;
    protected:
        QNetworkAccessManager* mgr;
        QNetworkReply* reply;
        QFile* file;
};

class IDownloader : public IOperation
{
        Q_OBJECT

    public:
        explicit IDownloader(QObject* parent = 0, const QString& siteName = 0): IOperation(parent, siteName)
        {
        }

        virtual ~IDownloader() {}

    protected:
        virtual void setupUrlAndFileByDate() = 0;
        virtual void launchDownloadingProcess() = 0;
        QString urlForDownload;
        QString fileForSave;
    signals:
        void fetchedGamingMonth(int);
        void fetchedGamingDay(int);

};

#endif // IDOWNLOADER_H
