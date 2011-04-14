#include <QDir>
#include <QHeaderView>
#include <QtNetwork/QNetworkReply>

#include "constants.h"

#include "presentation.h"
//Downloaders
#include "downloadergamingmonth.h"
#include "downloaderkhlrugamingday.h"

//Parsers
#include "parsegamingmonth.h"
#include "parserkhlrugamingday.h"

//Readers
#include "rwkhlrugamingday.h"
#include "rwkhlrugamingday_tmp.h"

//Runner
#include "qthreadrunner.h"


//TODO: файлы должны писаться только одним объектом, а читаться могут несколькими
//TODO:  ускорить работу парсера(новый механизм?) - отдельно счета и команды
//TODO: прокси для аппликейшена

presentation::presentation(IView* _view)
{
    view = _view;
    QNetworkProxy proxy;
    proxy.setType(QNetworkProxy::HttpProxy);
    proxy.setHostName("172.18.0.1");
    proxy.setPort(3128);
    proxy.setUser(QString());
    proxy.setPassword(QString());
    QNetworkProxy::setApplicationProxy(proxy);

    tableModel = new QStandardItemModel(this);

    view->table()->setModel(tableModel);

    createDownloadersList();
    createParsersList();
    createReadersList();
    createRunnersList();

    connectOnEvents();

    qDebug() << "Main thread" << ":" << QThread::currentThreadId();

}

void presentation::createReadersList()
{
    qDebug();
    readers = new OperationPool(this);
    readers->appendOperation(new RWKhlRuGamingMonth(readers));
    readers->appendOperation(new RWKhlRuGamingDay(readers));
}

void presentation::connectOnEvents()
{
    connect(view, SIGNAL(GamingDaySelected(const QDate&)), this,
            SLOT(gamingDaySelected(const QDate&)), Qt::AutoConnection);
    //Month
    connect(downloaders->getOperationByName("www.khl.ru"), SIGNAL(fetchedGamingMonth(int)), this,
            SLOT(downloadMonthResultsFinished(int)), Qt::QueuedConnection);
    connect(parsers->getOperationByName("www.khl.ru"), SIGNAL(parsedGamingMonth()), this,
            SLOT(parsingMonthFinished()), Qt::QueuedConnection);
    connect(readers->getOperationByName("www.khl.ru"), SIGNAL(FileNotExistToReading()), this,
            SLOT(EmptyReadingFile()), Qt::QueuedConnection);
    connect(readers->getOperationByName("www.khl.ru"), SIGNAL(ReadingComplete()), this,
            SLOT(fillMatchesTable()), Qt::QueuedConnection);
    //Day
    connect(downloaders->getOperationByName("www.khl.ru-day"), SIGNAL(fetchedGamingDay(int)), this,
            SLOT(downloadDayResultsFinished(int)), Qt::QueuedConnection);
    connect(parsers->getOperationByName("www.khl.ru-day"), SIGNAL(parsedGamingDay()), this,
            SLOT(parsingDayFinished()), Qt::QueuedConnection);
    connect(readers->getOperationByName("www.khl.ru-day"), SIGNAL(ReadingTodayResultsComplete()), this,
            SLOT(fillMatchesTodayTable()), Qt::QueuedConnection);
}

void presentation::downloadDayResultsFinished(int err)
{
    if (err == QNetworkReply::NoError)
    {
        qDebug()<<"Current day information downloaded. Start parser";
        view->setStatus(tr("Parsing downloaded matches info for current day") + selectedDay.toString("dd.MM.yy"));
        parsers->getOperationByName("www.khl.ru-day")->setDate(selectedDay);
        runners->startRunnerByName("www.khl.ru-parser-day");
    }
    else
    {
        view->setStatus(tr("Downloading failed. See connection state and your proxy settings"));
    }
}

void presentation::fillMatchesTodayTable()
{
    qDebug()<<"Reading complete";
    bool mayShowResults = readers->getOperationByName("www.khl.ru")->date() == selectedDay;
    //filtering by date
    if (mayShowResults)
    {

    }
    else
    {
        qDebug()<<"Stopping update";
        runners->getRunner("www.khl.ru-downloader-day")->stopExec();
    }
}

void presentation::fillMatchesTable()
{
    qDebug() << "View match info";

    bool mayShowResults = readers->getOperationByName("www.khl.ru")->date() == selectedDay;

    //Filtering by date
    if (mayShowResults)
    {
        view->setStatus(QString(tr("Matches for ") + selectedDay.toString("dd.MM.yy")));
        qDebug() << view->status();
        tableModel->clear();
        tableModel->setHorizontalHeaderLabels(QStringList() << tr("Home") << tr("Away") << tr("Count") << tr("State"));
        QStringList teams = ((IRWData*)(readers->getOperationByName("www.khl.ru")))->teams();
        QStringList counts = ((IRWData*)(readers->getOperationByName("www.khl.ru")))->counts();
        qDebug() << "Teams" << ":" << teams;
        qDebug() << "Counts" << ":" << counts;
        int cteam = teams.count();
        int ccount = counts.count();
        for (int i = 0; i < cteam; ++i)
        {
            QList<QStandardItem*> row;
            qDebug() << "home" << ":" << (teams[i]).section("-", 0, 0);
            qDebug() << "away" << ":" << (teams[i]).section("-", 1, 1);
            QStandardItem* homeitem = new QStandardItem((teams[i]).section("-", 0, 0));
            QStandardItem* awayitem = new QStandardItem((teams[i]).section("-", 1, 1));
            QStandardItem* countitem = new QStandardItem();
            if (i < ccount)
            {
                countitem->setText(counts[i]);
            }
            QStandardItem* stateitem = new QStandardItem("Ended");

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

}

void presentation::EmptyReadingFile()
{
    qDebug() << "Sorry, empty reading file";
    //TODO: create question
    view->setStatus(tr("Downloading matches info for ") + selectedDay.toString("dd.MM.yy"));
    downloaders->getOperationByName("www.khl.ru")->setDate(selectedDay);
    runners->startRunnerByName("www.khl.ru-downloader");
}

void presentation::gamingDaySelected(const QDate& gameDay)
{
    qDebug() << gameDay;
    selectedDay = gameDay;
    if ( gameDay != QDate::currentDate() )
    {
        qDebug()<<"Loading past information";
        readers->getOperationByName("www.khl.ru")->setDate(selectedDay);
        runners->startRunnerByName("www.khl.ru-reader");
    }
    else
    {
        qDebug()<<"Loading current info";
        view->setStatus(tr("Downloading match info for current day ") + selectedDay.toString("dd.MM.yy"));
        downloaders->getOperationByName("www.khl.ru-day")->setDate(selectedDay);
        runners->startRunnerByName("www.khl.ru-downloader-day");
    }
}

void presentation::downloadMonthResultsFinished(int error)
{
    if (error == QNetworkReply::NoError)
    {
        qDebug() << "Download successfully finished. Start parsing";
        view->setStatus(tr("Parsing downloaded matches info for ") + selectedDay.toString("dd.MM.yy"));
        parsers->getOperationByName("www.khl.ru")->setDate(selectedDay);
        runners->startRunnerByName("www.khl.ru-parser");
    }
    else
    {
        view->setStatus(tr("Downloading failed. See connection state and your proxy settings"));
    }
}

void presentation::parsingMonthFinished()
{
    qDebug() << "Parsing successfully finished. Start reading.";
    readers->getOperationByName("www.khl.ru")->setDate(selectedDay);
    runners->startRunnerByName("www.khl.ru-reader");
}

void presentation::parsingDayFinished()
{
     qDebug() << "Parsing successfully finished. Start reading.";
     readers->getOperationByName("www.khl.ru-day")->setDate(selectedDay);
     runners->startRunnerByName("www.khl.ru-reader-day");
}

void presentation::createDownloadersList()
{
    downloaders = new OperationPool(this);
    downloaders->appendOperation(new DownKhlRuGamingMonth(downloaders));
    downloaders->appendOperation(new DownKhlRuGamingDay(downloaders));
}

void presentation::createParsersList()
{
    parsers = new OperationPool(this);
    parsers->appendOperation(new ParseKhlRuGamingMonth(parsers));
    parsers->appendOperation(new ParserKhlRuGamingDay(parsers));
}

void presentation::createRunnersList()
{
    runners = new QThreadRunnerPool(this);
    runners->appendRunner(new QThreadOneRunner("www.khl.ru-downloader", downloaders->getOperationByName("www.khl.ru")));
    runners->appendRunner(new QThreadOneRunner("www.khl.ru-parser", parsers->getOperationByName("www.khl.ru")));
    runners->appendRunner(new QThreadOneRunner("www.khl.ru-reader", readers->getOperationByName("www.khl.ru")));
    runners->appendRunner(new QThreadPeriodRunner("www.khl.ru-downloader-day", downloaders->getOperationByName("www.khl.ru-day")));
    runners->appendRunner(new QThreadOneRunner("www.khl.ru-parser-day", parsers->getOperationByName("www.khl.ru-day")));
    runners->appendRunner(new QThreadOneRunner("www.khl.ru-reader-day", readers->getOperationByName("www.khl.ru-day")));
}
