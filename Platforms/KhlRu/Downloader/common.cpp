#include "common.h"
#include "constants.h"
//HTTP reciever
KhlRuReceiver::KhlRuReceiver(QNetworkAccessManager *_mgr, QFile *_file, const QString &urlForDownload):
        IReceiver(_mgr, _file)
{
    reply = mgr->get(QNetworkRequest(QUrl(urlForDownload)));

    qDebug()<<"3:"<<connect(reply, SIGNAL(finished()), this, SLOT(httpFinished()), Qt::DirectConnection);
    qDebug()<<"4:"<<connect(reply, SIGNAL(readyRead()), this, SLOT(httpReadyRead()), Qt::DirectConnection);
}

void KhlRuReceiver::httpFinished()
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

void KhlRuReceiver::httpReadyRead()
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

void DownloaderKhlRu::executeDownloadingProcess()
{
    // TODO: move to parent
    qDebug() << QTime::currentTime() << ":" << QThread::currentThreadId();
    // TODO: запускать процесс только в случае отсутствия или старого файла
    setupUrlAndFileByDate();
    launchDownloadingProcess();
}
