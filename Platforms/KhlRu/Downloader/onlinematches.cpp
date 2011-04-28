#include <QDir>

#include "onlinematches.h"


//Downloader
void DownKhlRuGamingDay::run()
{
    executeDownloadingProcess();
}

void DownKhlRuGamingDay::setupUrlAndFileByDate()
{
    qDebug() << QTime::currentTime() << ":" << QThread::currentThreadId();
    urlForDownload = QString(KhlRuUrl);
    QString newDir = QString(QDir::currentPath() + "/" + ResTmpDownloadPath + KhlRuName + CurrentGameDay);
    fileForSave = newDir + "current.html";
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

void DownKhlRuGamingDay::launchDownloadingProcess()
{
    qDebug() << QTime::currentTime() << ":" << QThread::currentThreadId();

    QNetworkAccessManager *mgr = new QNetworkAccessManager();

    KhlRuReceiver* receiver = new KhlRuReceiver(mgr,&file, urlForDownload);

    qDebug()<<"1:"<<connect(receiver, SIGNAL(finished(int)), this, SIGNAL(fetchedGamingDay(int)), Qt::QueuedConnection);
    qDebug()<<"2:"<<connect(receiver, SIGNAL(finished(int)), this, SLOT(finishDownload(int)), Qt::QueuedConnection);

    qDebug()<<"Launch ended";
}

void DownKhlRuGamingDay::finishDownload(int error)
{
    if (error != QNetworkReply::NoError)
    {
        emit endOperation();
    }
}

