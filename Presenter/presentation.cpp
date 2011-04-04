#include <QDir>
#include <QHeaderView>

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

    tableModel = new QStandardItemModel(this);

    view->table()->setModel(tableModel);

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
    connect(readers->getOperationByName("www.khl.ru"), SIGNAL(ReadingComplete()), this,
            SLOT(fillMatchesTable()), Qt::QueuedConnection);
}

void presentation::fillMatchesTable()
{
    qDebug()<<"View match info";
    tableModel->clear();
    tableModel->setHorizontalHeaderLabels(QStringList()<<tr("Home")<<tr("Away")<<tr("Count")<<tr("State"));
    QStringList teams = ((IRWData *)(readers->getOperationByName("www.khl.ru")))->teams();
    QStringList counts = ((IRWData *)(readers->getOperationByName("www.khl.ru")))->counts();
    qDebug()<<"Teams"<<":"<< teams;
    qDebug()<<"Counts"<<":"<<counts;
    int cteam = teams.count();
    int ccount = counts.count();
    for(int i = 0; i < cteam; ++i)
    {
        QList<QStandardItem *> row;
        qDebug()<<"home"<<":"<<(teams[i]).section("-",0,0);
        qDebug()<<"away"<<":"<<(teams[i]).section("-",1,1);
        QStandardItem *homeitem = new QStandardItem((teams[i]).section("-",0,0));
        QStandardItem *awayitem = new QStandardItem((teams[i]).section("-",1,1));
        QStandardItem *countitem = new QStandardItem();
        if( i < ccount)
        {
            countitem->setText(counts[i]);
        }
        QStandardItem *stateitem = new QStandardItem("Ended");

        homeitem->setEditable(false);
        awayitem->setEditable(false);
        countitem->setEditable(false);
        stateitem->setEditable(false);


        row.append(homeitem);
        row.append(awayitem);
        row.append(countitem);
        row.append(stateitem);

        tableModel->appendRow(row);
    }
    view->table()->horizontalHeader()->setResizeMode(0, QHeaderView::Stretch);;
    view->table()->horizontalHeader()->setResizeMode(1, QHeaderView::Stretch);
    view->table()->horizontalHeader()->setResizeMode(2, QHeaderView::Stretch);
    view->table()->horizontalHeader()->setResizeMode(3, QHeaderView::Stretch);


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
   parsers->appendOperation(new ParseKhlRuGamingMonth(parsers));
}

void presentation::createRunnersList()
{
    runners = new QThreadRunnerPool(this);
    runners->appendRunner(new QThreadOneRunner("www.khl.ru-downloader", downloaders->getOperationByName("www.khl.ru") ));
    runners->appendRunner(new QThreadOneRunner("www.khl.ru-parser", parsers->getOperationByName("www.khl.ru")));
    runners->appendRunner(new QThreadOneRunner("www.khl.ru-reader", readers->getOperationByName("www.khl.ru")));
}
