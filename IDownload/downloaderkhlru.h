#ifndef DOWNLOADERKHLRU_H
#define DOWNLOADERKHLRU_H

#include <QThread>
#include <QDateTime>
#include <QFile>

#include "idownloader.h"

class DownloaderKhlRu : public IDownloader
{
        Q_OBJECT
    public:
        explicit DownloaderKhlRu(QObject* parent = 0, const QString& siteName = "www.khl.ru") : IDownloader(parent, siteName)
        {
        }
        virtual ~DownloaderKhlRu() {}
    signals:
};

#endif // DOWNLOADERKHLRU_H
