#include <QDir>

#include "constants.h"

#include "presentation.h"
//Downloaders
#include "downloadergamingmonth.h"

//Parsers
#include "parserkhlru.h"

//Runner
#include "qthreadrunner.h"


presentation::presentation(IView* _view)
{
    view = _view;
    createDownloadersList();
    createParsersList();
    //CreateWriters
    createRunnersList();

    connectOnEvents();

    qDebug()<<"Main thread"<<":"<<QThread::currentThreadId();
}

void presentation::connectOnEvents()
{
    connect(view, SIGNAL(GamingDaySelected(const QDate&)), this,
            SLOT(gamingDaySelected(const QDate&)), Qt::AutoConnection);
    connect(downloaders->getOperationByName("www.khl.ru"), SIGNAL(fetchedGamingMonth()), this,
            SLOT(downloadFinished()), Qt::QueuedConnection);
}

void presentation::gamingDaySelected(const QDate& gameDay)
{
    qDebug()<<gameDay;
    ((IDownloader *)(downloaders->getOperationByName("www.khl.ru")))->setDate(gameDay);
    runners->startRunnerByName("www.khl.ru-downloader");
}

void presentation::downloadFinished()
{
    qDebug()<<"Download finished. Start parsing";
    runners->startRunnerByName("www.khl.ru-parser");
}

void presentation::createDownloadersList()
{
    downloaders = new OperationPool(this);
    //TEST
//    _date =  QDate(2011, 03, 29);
//    _typeProxy = QNetworkProxy::HttpProxy;
//    _hostProxy = "172.18.0.1";
//    _portProxy = 3128;
//    _userProxy  = QString();
//    _pwdProxy = QString();
  DownKhlRuGamingMonth *el = new DownKhlRuGamingMonth(downloaders);
  el->setDate(QDate(2008, 10, 29));
  el->setTypeProxy(QNetworkProxy::HttpProxy);
  el->setHostProxy("172.18.0.1");
  el->setPortProxy(3128);
  el->setUserProxy(QString());
  el->setPwdProxy(QString());
  downloaders->appendOperation(el);
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
