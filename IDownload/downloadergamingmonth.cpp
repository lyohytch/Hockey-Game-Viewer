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
    setupNetManager();
    launchReceiver();

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
            fileForSave = QString::number(date().month()) + ".html";
            break;
        }
        if (isPlayOffs(date(), season))
        {
            urlForDownload += getAddToUrl(playoffs, season.yearPlayOff) + "/" + QString::number(date().month());
            newDir += QString::number(season.yearStart) + "-" + QString::number(season.yearEnd) + "/";
            fileForSave = QString::number(date().month()) + ".html";
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
    //Check for file
    QString fname = newDir + "/" + fileForSave;
    file = new QFile(fname);
    if ( !file->exists())
    {
        file->open(QIODevice::WriteOnly);
    }
    else
    {
        qDebug()<<"File exists and newest";
        emit fetchedGamingMonth();
        emit endOperation();
    }
}

void DownKhlRuGamingMonth::setupNetManager()
{
    mgr = new QNetworkAccessManager();
    mgr->setProxy(QNetworkProxy(QNetworkProxy::ProxyType(this->typeProxy()),
                                this->hostProxy(), this->portProxy(),
                                this->userProxy(), this->pwdProxy()));
}

void DownKhlRuGamingMonth::launchReceiver()
{
    reply = mgr->get(QNetworkRequest(QUrl(urlForDownload)));

    KhlRuGamingMonthReceiver* receiver = new KhlRuGamingMonthReceiver(mgr, reply, file);

    connect(receiver, SIGNAL(finished()), this, SIGNAL(fetchedGamingMonth()), Qt::QueuedConnection);
    connect(receiver, SIGNAL(finished()), this, SIGNAL(endOperation()), Qt::QueuedConnection);

    connect(reply, SIGNAL(finished()), receiver, SLOT(httpFinished()), Qt::QueuedConnection);
    connect(reply, SIGNAL(readyRead()), receiver, SLOT(httpReadyRead()), Qt::QueuedConnection);
}

//HTTP reciever
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

    emit finished();

    reply->deleteLater();
    reply = 0;
    file->close();

    //    //TODO: need to delete objects
    mgr->deleteLater();
    mgr = 0;
}

void KhlRuGamingMonthReceiver::httpReadyRead()
{
    qDebug() << QTime::currentTime() << ":" << QThread::currentThreadId();
    if (file)
    {
        qDebug() << "Write into file";
        file->write(reply->readAll());
    }
}
