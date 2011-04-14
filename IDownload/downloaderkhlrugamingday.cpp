#include <QDir>

#include "downloaderkhlrugamingday.h"


//Downloader
void DownKhlRuGamingDay::run()
{
    // TODO: move to parent
    qDebug() << QTime::currentTime() << ":" << QThread::currentThreadId();
    // TODO: запускать процесс только в случае отсутствия или старого файла
    setupUrlAndFileByDate();
    launchDownloadingProcess();
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

    KhlRuGamingDayReceiver* receiver = new KhlRuGamingDayReceiver(mgr,&file, urlForDownload);

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

//HTTP reciever
KhlRuGamingDayReceiver::KhlRuGamingDayReceiver(QNetworkAccessManager *_mgr, QFile *_file, const QString &urlForDownload):
        IReceiver(_mgr, _file)
{
    reply = mgr->get(QNetworkRequest(QUrl(urlForDownload)));

    qDebug()<<"3:"<<connect(reply, SIGNAL(finished()), this, SLOT(httpFinished()), Qt::DirectConnection);
    qDebug()<<"4:"<<connect(reply, SIGNAL(readyRead()), this, SLOT(httpReadyRead()), Qt::DirectConnection);
}

void KhlRuGamingDayReceiver::httpFinished()
{
    qDebug() << QTime::currentTime() << ":" << QThread::currentThreadId();
    QVariant redirectionTarget = reply->attribute(QNetworkRequest::RedirectionTargetAttribute);
    QNetworkReply::NetworkError err;
    if (err = reply->error())
    {
        qDebug() << reply->errorString();
    }
    else if (!redirectionTarget.isNull())
    {
        qDebug() << "Redirection";
        return;
    }
    else
    {
        qDebug() << "Downloaded url";
    }

    reply->deleteLater();

    mgr->deleteLater();

    file->close();
    this->deleteLater();

    emit finished(err);
}

void KhlRuGamingDayReceiver::httpReadyRead()
{
    qDebug() << QTime::currentTime() << ":" << QThread::currentThreadId();
    if ( file && !file->isOpen() )
    {
        qDebug()<<"Open file for save data";
        file->open(QIODevice::WriteOnly);
    }
    if (file)
    {
        qDebug() << "Write into file";
        file->write(reply->readAll());
    }
}
