#include <QDir>
#include <QDate>

#include "constants.h"
#include "downloadergamingmonth.h"

void DownKhlRuGamingMonth::run()
{
    qDebug() << QTime::currentTime() << ":" << QThread::currentThreadId();

    setupUrlAndFileByDate();
    setupNetManager();

    launchReceiver();

}

void DownKhlRuGamingMonth::setupUrlAndFileByDate()
{
    qDebug() << QTime::currentTime() << ":" << QThread::currentThreadId();
    url = KhlRuUrl + GameMonth;
    fname = QString();
    newDir = QDir::currentPath() + "/" + ResTmpDownloadPath + KhlRuName + GameMonth;
    qDebug()<<newDir;
    foreach (Season season , seasons)
    {
        if ( isRegular( date().year(), date().month(), season ) )
        {

            url += getAddToUrl(regulars, season.yearStart) + "/" + QString::number(date().month()) + "/";
            newDir += QString::number(season.yearStart) + "-" + QString::number(season.yearEnd) + "/";
            fname = QString::number(date().month()) + ".html";
            break;
        }
        if ( isPlayOffs( date().year(), date().month(), season ) )
        {
            url += getAddToUrl(playoffs, season.yearPlayOff) + "/" + QString::number(date().month());
            newDir += QString::number(season.yearStart) + "-" + QString::number(season.yearEnd) + "/";
            fname = QString::number(date().month()) + ".html";
            break;
        }
    }

    qDebug()<<"url"<<":"<<url;
    qDebug()<<"fname"<<":"<<fname;
    qDebug()<<"newDir"<<":"<<newDir;
    QDir dir(newDir);
    if (!dir.exists())
    {
        qDebug()<<"Dir isn't exist ";
        dir.mkpath(newDir);
    }
    file = new QFile(newDir + "/" + fname);
    file->open(QIODevice::WriteOnly);
}

void DownKhlRuGamingMonth::setupNetManager()
{
    mgr = new QNetworkAccessManager();
    mgr->setProxy( QNetworkProxy(QNetworkProxy::ProxyType(this->typeProxy()),
                                 this->hostProxy(), this->portProxy(),
                                 this->userProxy(), this->pwdProxy()));
}

void DownKhlRuGamingMonth::launchReceiver()
{
    reply = mgr->get(QNetworkRequest(QUrl(url)));

    KhlRuGamingMonthReceiver *receiver = new KhlRuGamingMonthReceiver(mgr, reply, file);

    connect(receiver, SIGNAL(finished()), this, SIGNAL(fetchedGamingMonth()), Qt::QueuedConnection);

    connect(reply, SIGNAL(finished()), receiver, SLOT(httpFinished()), Qt::QueuedConnection);
    connect(reply,SIGNAL(readyRead()), receiver, SLOT(httpReadyRead()), Qt::QueuedConnection);
}

QString DownKhlRuGamingMonth::getAddToUrl(const QList<MapValue> & list, int key)
{
    foreach (MapValue el, list)
    {
        if (key == el.year)
        {
            return el.addUrl;
        }
    }
    return QString();
}

void KhlRuGamingMonthReceiver::httpFinished()
{
    qDebug() << QTime::currentTime() << ":" << QThread::currentThreadId();
    QVariant redirectionTarget = reply->attribute(QNetworkRequest::RedirectionTargetAttribute);
    if(reply->error())
    {
        qDebug()<<reply->errorString();
    }
    else if ( !redirectionTarget.isNull())
    {
        qDebug()<<"Redirection";
        return;
    }
    else
    {
       qDebug()<<"Downloaded url";
    }
    reply->deleteLater();
    reply = 0;
    file->close();

//    //TODO: need to delete objects
//    file->deleteLater();
//    file = 0;

    mgr->deleteLater();
    mgr = 0;

    emit finished();
}

void KhlRuGamingMonthReceiver::httpReadyRead()
{
    qDebug() << QTime::currentTime() << ":" << QThread::currentThreadId();
    if (file)
    {
        qDebug()<<"Write into file";
        file->write(reply->readAll());
    }
}
