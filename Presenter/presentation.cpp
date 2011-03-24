#include <QtNetwork/QNetworkProxy>
#include <QtNetwork/QNetworkAccessManager>

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
    view->setTypeProxy(QNetworkProxy::HttpProxy);
    view->setHostProxy("172.18.0.1");
    view->setPortProxy(3128);
    qDebug()<<"view"<<":"<<view->typeProxy();
    qDebug()<<"view"<<":"<<view->hostProxy();
    qDebug()<<"view"<<":"<<view->portProxy();
    qDebug()<<"view"<<":"<<view->userProxy();
    qDebug()<<"view"<<":"<< view->pwdProxy();
    QNetworkAccessManager *mgr = new QNetworkAccessManager(this);
    mgr->setProxy( new QNetworkProxy(view->typeProxy(), view->hostProxy(), view->portProxy(),
                                     view->userProxy(), view->pwdProxy()));

    delete mgr;

    createDownloadersList();
    createParsersList();
    //CreateWriters
    createRunnersList();

    connectOnEvents();

    qDebug()<<"Main thread"<<":"<<QThread::currentThreadId();
    runners->start();
}

void presentation::connectOnEvents()
{
    connect(view, SIGNAL(GamingDaySelected(const QDate&)), this,
            SLOT(gamingDaySelected(const QDate&)), Qt::AutoConnection);
}

void presentation::gamingDaySelected(const QDate& gameDay)
{
    qDebug()<<gameDay;

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
    runners->appendRunner(new QThreadRunner("www.khl.ru-downloader", downloaders->getOperationByName("www.khl.ru") ));
    runners->appendRunner(new QThreadRunner("www.khl.ru-parser", parsers->getOperationByName("www.khl.ru")));
}
