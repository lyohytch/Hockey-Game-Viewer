#include <QDir>
#include <QDate>

#include "constants.h"
#include "downloadergamingmonth.h"

//Downloader
void DownKhlRuGamingMonth::run()
{
    // TODO: move to parent
    qDebug() << QTime::currentTime() << ":" << QThread::currentThreadId();
    // TODO: запускать процесс только в случае отсутствия или старого файла
    setupUrlAndFileByDate();
    launchDownloadingProcess();
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
    mgr->setProxy(QNetworkProxy(QNetworkProxy::ProxyType(this->typeProxy()),
                                this->hostProxy(), this->portProxy(),
                                this->userProxy(), this->pwdProxy()));


    KhlRuGamingMonthReceiver* receiver = new KhlRuGamingMonthReceiver(mgr,&file, urlForDownload);

    qDebug()<<"1:"<<connect(receiver, SIGNAL(finished()), this, SIGNAL(fetchedGamingMonth()), Qt::QueuedConnection);
    qDebug()<<"2:"<<connect(receiver, SIGNAL(finished()), this, SIGNAL(endOperation()), Qt::QueuedConnection);

    qDebug()<<"Launch ended";
}

//HTTP reciever
KhlRuGamingMonthReceiver::KhlRuGamingMonthReceiver(QNetworkAccessManager *_mgr, QFile *_file, const QString &urlForDownload):
        IReceiver(_mgr, _file)
{
    reply = mgr->get(QNetworkRequest(QUrl(urlForDownload)));

    qDebug()<<"3:"<<connect(reply, SIGNAL(finished()), this, SLOT(httpFinished()), Qt::DirectConnection);
    qDebug()<<"4:"<<connect(reply, SIGNAL(readyRead()), this, SLOT(httpReadyRead()), Qt::DirectConnection);
}

void KhlRuGamingMonthReceiver::httpFinished()
{
    qDebug() << QTime::currentTime() << ":" << QThread::currentThreadId();
    QVariant redirectionTarget = reply->attribute(QNetworkRequest::RedirectionTargetAttribute);
    if (reply->error())
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

    emit finished();
}

void KhlRuGamingMonthReceiver::httpReadyRead()
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
