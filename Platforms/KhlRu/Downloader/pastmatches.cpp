#include <QDir>
#include <QDate>

#include "constants.h"
#include "pastmatches.h"

//Downloader
void DownKhlRuGamingMonth::run()
{
    executeDownloadingProcess();
}

QString DownKhlRuGamingMonth::getAddToUrl(const QList<MapValue> & list, int key)
{
    foreach(MapValue el, list)
    {
        if (key == el.year)
        {
            return el.addUrl;
        }
    }
    return QString();
}

void DownKhlRuGamingMonth::setupUrlAndFileByDate()
{
    qDebug() << QTime::currentTime() << ":" << QThread::currentThreadId();
    urlForDownload = QString(KhlRuUrl + GameMonth);
    fileForSave = QString();
    QString newDir = QString(QDir::currentPath() + "/" + ResTmpDownloadPath + KhlRuName + GameMonth);
    qDebug() << newDir;
    foreach(Season season , seasons)
    {
        if (isRegular(date(), season))
        {

            urlForDownload += getAddToUrl(regulars, season.yearStart) + "/" + QString::number(date().month()) + "/";
            newDir += QString::number(season.yearStart) + "-" + QString::number(season.yearEnd) + "/";
            fileForSave = newDir + "/" + QString::number(date().month()) + ".html";
            break;
        }
        if (isPlayOffs(date(), season))
        {
            urlForDownload += getAddToUrl(playoffs, season.yearPlayOff) + "/" + QString::number(date().month()) + "/";
            newDir += QString::number(season.yearStart) + "-" + QString::number(season.yearEnd) + "/";
            fileForSave = newDir + "/" + QString::number(date().month()) + ".html";
            break;
        }
    }

    qDebug() << "url" << ":" << urlForDownload;
    qDebug() << "fname" << ":" << fileForSave;
    qDebug() << "newDir" << ":" << newDir;
    QDir dir(newDir);
    if (!dir.exists())
    {
        qDebug() << "Dir isn't exist ";
        dir.mkpath(newDir);
    }
    file.setFileName(fileForSave);
}

void DownKhlRuGamingMonth::launchDownloadingProcess()
{
    qDebug() << QTime::currentTime() << ":" << QThread::currentThreadId();

    QNetworkAccessManager *mgr = new QNetworkAccessManager();

    KhlRuReceiver* receiver = new KhlRuReceiver(mgr,&file, urlForDownload);

    qDebug()<<"1:"<<connect(receiver, SIGNAL(finished(int)), this, SIGNAL(fetchedGamingMonth(int)), Qt::QueuedConnection);
    qDebug()<<"2:"<<connect(receiver, SIGNAL(finished(int)), this, SIGNAL(endOperation()), Qt::QueuedConnection);
    qDebug()<<"Launch ended";
}
