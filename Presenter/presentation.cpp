#include <QDir>

#include "constants.h"

#include "presentation.h"
//Downloaders
#include "downloadergamingmonth.h"

//Parsers
#include "parsegamingmonth.h"

//Readers
#include "rwkhlrugamingday.h"

//Runner
#include "qthreadrunner.h"




presentation::presentation(IView* _view)
{
    view = _view;
    createDownloadersList();
    createParsersList();
    createReadersList();
    createRunnersList();

    connectOnEvents();

    qDebug()<<"Main thread"<<":"<<QThread::currentThreadId();

    //Test
//    selectedDay = QDate(2011, 01, 10);
//    qDebug()<<"Download finished. Start parsing";
//    parsers->getOperationByName("www.khl.ru")->setDate(selectedDay);
//    runners->getRunner("www.khl.ru-downloader")->stopExec();
//    runners->startRunnerByName("www.khl.ru-parser");

}

void presentation::createReadersList()
{
    qDebug();
    readers = new OperationPool(this);
    readers->appendOperation(new RWKhlRuGamingDay(readers));
}

void presentation::connectOnEvents()
{
    connect(view, SIGNAL(GamingDaySelected(const QDate&)), this,
            SLOT(gamingDaySelected(const QDate&)), Qt::AutoConnection);
    connect(downloaders->getOperationByName("www.khl.ru"), SIGNAL(fetchedGamingMonth()), this,
            SLOT(downloadFinished()), Qt::QueuedConnection);
    connect(parsers->getOperationByName("www.khl.ru"), SIGNAL(parsedGamingMonth()), this,
            SLOT(parsingFinished()), Qt::QueuedConnection);
    connect(readers->getOperationByName("www.khl.ru"), SIGNAL(FileNotExistToReading()), this,
            SLOT(EmptyReadingFile()), Qt::QueuedConnection);
}

void presentation::EmptyReadingFile()
{
    qDebug()<<"Sorry, empty reading file";
    qDebug()<<"Do I repeat downloading?";
}

void presentation::gamingDaySelected(const QDate& gameDay)
{
    qDebug()<<gameDay;
    selectedDay = gameDay;
    downloaders->getOperationByName("www.khl.ru")->setDate(selectedDay);
    runners->startRunnerByName("www.khl.ru-downloader");
}

void presentation::downloadFinished()
{
    qDebug()<<"Download successfully finished. Start parsing";
    parsers->getOperationByName("www.khl.ru")->setDate(selectedDay);
    runners->startRunnerByName("www.khl.ru-parser");
}

void presentation::parsingFinished()
{
    qDebug()<<"Parsing successfully finished. Start reading.";
    readers->getOperationByName("www.khl.ru")->setDate(selectedDay);
    runners->startRunnerByName("www.khl.ru-reader");
}

void presentation::createDownloadersList()
{
    downloaders = new OperationPool(this);
  DownKhlRuGamingMonth *el = new DownKhlRuGamingMonth(downloaders);
  el->setDate(QDate(2008, 10, 29));
  el->setTypeProxy(QNetworkProxy::NoProxy);
  el->setHostProxy(QString());
  el->setPortProxy(0);
  el->setUserProxy(QString());
  el->setPwdProxy(QString());
  downloaders->appendOperation(el);
}

void presentation::createParsersList()
{
   parsers = new OperationPool(this);
   parsers->appendOperation(new ParseKhlRuGamingMonth(parsers));
}

void presentation::createRunnersList()
{
    runners = new QThreadRunnerPool(this);
    runners->appendRunner(new QThreadOneRunner("www.khl.ru-downloader", downloaders->getOperationByName("www.khl.ru") ));
    runners->appendRunner(new QThreadOneRunner("www.khl.ru-parser", parsers->getOperationByName("www.khl.ru")));
    runners->appendRunner(new QThreadOneRunner("www.khl.ru-reader", readers->getOperationByName("www.khl.ru")));
}
