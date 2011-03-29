#include <QDir>

#include "constants.h"
#include "constants_downloader.h"
#include "downloadergamingmonth.h"

void DownKhlRuGamingMonth::run()
{
    qDebug() << QTime::currentTime() << ":" << QThread::currentThreadId();
    QString downDir = ResTmpDownloadPath + KhlRuName + date().year() + "/";
    qDebug()<<"Date: "<<date();
    qDebug() <<"Directory:"<< downDir;
    QDir dwnDir(downDir);
    if (!dwnDir.exists())
    {
        dwnDir.mkpath(downDir);
    }

    file = new QFile(downDir + date().month() + ".html");
    mgr = new QNetworkAccessManager(this);
    mgr->setProxy( QNetworkProxy(((QNetworkProxy::ProxyType)typeProxy()), hostProxy(), portProxy(),
                                     userProxy(), pwdProxy()));

    connect(reply, SIGNAL(finished()), this,
            SLOT(httpFinished()));
    connect(reply,SIGNAL(readyRead()), this,
            SLOT(httpReadyRead()));


    reply = mgr->get(QNetworkRequest(QUrl(QString::fromUtf8("http://www.khl.ru/players/?letter=É"))));
}

void DownKhlRuGamingMonth::httpFinished()
{
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

void DownKhlRuGamingMonth::httpReadyRead()
{
    qDebug();
    if (file)
    {
        qDebug()<<"Write to file";
        file->write(reply->readAll());
    }
}
