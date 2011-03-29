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


//    //Download www.khl.ru
//    QString path = "../Resources/tmp/www.khl.ru/";
//    QDir::mkpath(path);
//    file = new QFile("index.html");
//    file->open(QIODevice::WriteOnly);
//    view->setTypeProxy(QNetworkProxy::HttpProxy);
//    view->setHostProxy("172.18.0.1");
//    view->setPortProxy(3128);
//    view->setUserProxy(QString());
//    view->setPwdProxy(QString());
//    qDebug()<<"view"<<":"<<view->typeProxy();
//    qDebug()<<"view"<<":"<<view->hostProxy();
//    qDebug()<<"view"<<":"<<view->portProxy();
//    qDebug()<<"view"<<":"<<view->userProxy();
//    qDebug()<<"view"<<":"<< view->pwdProxy();
//    mgr = new QNetworkAccessManager(this);
//    mgr->setProxy( QNetworkProxy(((QNetworkProxy::ProxyType)view->typeProxy()), view->hostProxy(), view->portProxy(),
//                                     view->userProxy(), view->pwdProxy()));

//    reply = mgr->get(QNetworkRequest(QUrl(QString::fromUtf8("http://www.khl.ru/players/?letter=É"))));//Test:Season 8-9, Month - November
//    connect(reply, SIGNAL(finished()), this,
//            SLOT(httpFinished()));
//    connect(reply,SIGNAL(readyRead()), this,
//            SLOT(httpReadyRead()));

    createDownloadersList();
    createParsersList();
    //CreateWriters
    createRunnersList();

    connectOnEvents();

    qDebug()<<"Main thread"<<":"<<QThread::currentThreadId();
    runners->startRunnerByName("www.khl.ru-downloader");
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
//   DownKhlRuGamingMonth *el = new DownKhlRuGamingMonth(downloaders);
//   el->setDate(QDate(2011, 03, 29));
//   el->setTypeProxy(QNetworkProxy::HttpProxy);
//   el->setHostProxy("172.18.0.1");
//   el->setPortProxy(3128);
//   el->setUserProxy(QString());
//   el->setPwdProxy(QString());
   downloaders->appendOperation(new DownKhlRuGamingMonth(downloaders));
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
