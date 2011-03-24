#include "constants.h"

#include "presentation.h"
//Downloaders
#include "downloaderkhlru.h"

//Parsers
#include "parserkhlru.h"

//Runner
#include "qthreadrunner.h"


presentation::presentation(IView* _view)
{
    view = _view;


    //Download www.khl.ru
    file = new QFile("index.html");
    file->open(QIODevice::WriteOnly);
    view->setTypeProxy(QNetworkProxy::HttpProxy);
    view->setHostProxy("172.18.0.1");
    view->setPortProxy(3128);
    view->setUserProxy(QString());
    view->setPwdProxy(QString());
    qDebug()<<"view"<<":"<<view->typeProxy();
    qDebug()<<"view"<<":"<<view->hostProxy();
    qDebug()<<"view"<<":"<<view->portProxy();
    qDebug()<<"view"<<":"<<view->userProxy();
    qDebug()<<"view"<<":"<< view->pwdProxy();
    mgr = new QNetworkAccessManager(this);
    mgr->setProxy( QNetworkProxy(((QNetworkProxy::ProxyType)view->typeProxy()), view->hostProxy(), view->portProxy(),
                                     view->userProxy(), view->pwdProxy()));

    reply = mgr->get(QNetworkRequest(QUrl("http://www.khl.ru/calendar/")));
    connect(reply, SIGNAL(finished()), this,
            SLOT(httpFinished()));
    connect(reply,SIGNAL(readyRead()), this,
            SLOT(httpReadyRead()));

    createDownloadersList();
    createParsersList();
    //CreateWriters
    createRunnersList();

    connectOnEvents();

    qDebug()<<"Main thread"<<":"<<QThread::currentThreadId();
    runners->startRunnerByName("www.khl.ru-downloader");
}

void presentation::httpFinished()
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
}

void presentation::httpReadyRead()
{
    qDebug();
    if (file)
    {
        qDebug()<<"Write to file";
        file->write(reply->readAll());
    }
}

void presentation::connectOnEvents()
{
    connect(view, SIGNAL(GamingDaySelected(const QDate&)), this,
            SLOT(gamingDaySelected(const QDate&)), Qt::AutoConnection);
    connect(downloaders->getOperationByName("www.khl.ru"), SIGNAL(finish()), this,
            SLOT(downloadFinished()), Qt::QueuedConnection);
}

void presentation::gamingDaySelected(const QDate& gameDay)
{
    qDebug()<<gameDay;

}

void presentation::downloadFinished()
{
    qDebug()<<"Download finished. Start parsing";
    runners->startRunnerByName("www.khl.ru-parser");
}

void presentation::createDownloadersList()
{
    downloaders = new OperationPool(this);
    downloaders->appendOperation(new DownloaderKhlRu(downloaders));
}

void presentation::createParsersList()
{
   parsers = new OperationPool(this);
   parsers->appendOperation(new ParserKhlRu(parsers));
}

void presentation::createRunnersList()
{
    runners = new QThreadRunnerPool(this);
    runners->appendRunner(new QThreadPeriodRunner("www.khl.ru-downloader", downloaders->getOperationByName("www.khl.ru") ));
    runners->appendRunner(new QThreadOneRunner("www.khl.ru-parser", parsers->getOperationByName("www.khl.ru")));
}
