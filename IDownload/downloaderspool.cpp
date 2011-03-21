#include "downloaderspool.h"

DownloadersPool::DownloadersPool(QObject* parent) :
    QObject(parent)
{
}

IDownloader* DownloadersPool::getDownloaderByName(const QString& siteName)
{
    foreach(IDownloader * dl, _downloaders)
    {
        if (dl->targetSite() == siteName)
        {
            return dl;
        }
    }
    return 0;
}

void DownloadersPool::appendDownloader(IDownloader* downloader)
{
    _downloaders.append(downloader);
}

