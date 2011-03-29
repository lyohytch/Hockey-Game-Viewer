#include <QDir>

#include "constants.h"
#include "constants_downloader.h"
#include "downloadergamingmonth.h"

void DownKhlRuGamingMonth::run()
{
    qDebug() << QTime::currentTime() << ":" << QThread::currentThreadId();
    ReceiverKhlRuGamingMonth *rec = new ReceiverKhlRuGamingMonth("03.html");

    rec->setupFile("03.html");
    file = new QFile("03.html");
    file->open(QIODevice::WriteOnly);
    mgr = new QNetworkAccessManager();
    mgr->setProxy( QNetworkProxy(QNetworkProxy::HttpProxy, "172.18.0.1", 3128,
                                     QString(), QString()));

   reply = mgr->get(QNetworkRequest(QUrl(QString::fromUtf8("http://www.khl.ru/calendar/186/03/"))));

   QObject::connect(reply, SIGNAL(finished()), this,
                    SLOT(httpFinished()), Qt::QueuedConnection);
   QObject::connect(reply,SIGNAL(readyRead()), this,
                    SLOT(httpReadyRead()), Qt::QueuedConnection);
}

void ReceiverKhlRuGamingMonth::httpFinished()
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
       qDebug()<<"Downloaded index.html";
    }
    reply->deleteLater();
    reply = 0;
    file->close();

    emit fetchedGamingMonth();
}

void ReceiverKhlRuGamingMonth::httpReadyRead()
{
    qDebug() << QTime::currentTime() << ":" << QThread::currentThreadId();
    if (file)
    {
        qDebug()<<"Write to file";
        file->write(reply->readAll());
    }
}
