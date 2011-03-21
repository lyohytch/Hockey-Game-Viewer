#ifndef DOWNLOADERSPOOL_H
#define DOWNLOADERSPOOL_H

#include <QObject>
#include "idownloader.h"

class DownloadersPool : public QObject
{
        Q_OBJECT
    public:
        explicit DownloadersPool(QObject* parent = 0);

        IDownloader* getDownloaderByName(const QString& siteName);
        void appendDownloader(IDownloader* downloader);
    signals:

    public slots:

    private:
        QList<IDownloader*> _downloaders;

};


#endif // DOWNLOADERSPOOL_H
