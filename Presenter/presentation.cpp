#include <QDir>
#include <QtNetwork/QNetworkReply>

#include "constants.h"

#include "presentation.h"
//Downloaders
#include "Platforms/KhlRu/Downloader/d_pastmatches.h"
#include "Platforms/KhlRu/Downloader/d_onlinematches.h"

//Parsers
#include "Platforms/KhlRu/Parser/p_pastmatches.h"
#include "Platforms/KhlRu/Parser/p_onlinematches.h"

//Readers
#include "Platforms/KhlRu/Reader/r_pastmatches.h"
#include "Platforms/KhlRu/Reader/r_onlinematches.h"

//Runner
#include "qthreadrunner.h"

//TODO: выкинуть QtGui из интерфейсов
//TODO: разбить по модулям, имена файлов = имена классов
//TODO: компрессия временных данных?
//TODO: файлы должны писаться только одним объектом, а читаться могут несколькими
//TODO:  ускорить работу парсера(новый механизм?) - отдельно счета и команды
//TODO: прокси для аппликейшена
//TODO: у будущих матчей выставить статус в читальщике
//TODO: сделать проверку времени изменения файла - последовательность действий при этом
//TODO: форму с настройками: прокси, времени обновления сегодняшней инфы(обновление когда матч начался, и когда матч ещё не начался)

presentation::presentation(IView* _view, IViewSettings * _viewSettings)
{
    view = _view;

    viewSettings = _viewSettings;

    proxySettingsChanged();

    tableModel = new QStandardItemModel(this);

    view->setModel(tableModel);

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

    connect(viewSettings, SIGNAL(ProxySettingsChanged()), this,
            SLOT(proxySettingsChanged()), Qt::AutoConnection);
    //Month
    connect(downloaders->getOperationByName("www.khl.ru"), SIGNAL(fetchedGamingMonth(int)), this,
            SLOT(downloadMonthResultsFinished(int)), Qt::QueuedConnection);
    connect(parsers->getOperationByName("www.khl.ru"), SIGNAL(parsedGamingMonth()), this,
            SLOT(parsingMonthFinished()), Qt::QueuedConnection);
    connect(readers->getOperationByName("www.khl.ru"), SIGNAL(FileNotExistToReading()), this,
            SLOT(EmptyReadingFile()), Qt::QueuedConnection);
    connect(readers->getOperationByName("www.khl.ru"), SIGNAL(ReadingAnyDayComplete()), this,
            SLOT(fillMatchesTable()), Qt::QueuedConnection);
    //Day
    connect(downloaders->getOperationByName("www.khl.ru-day"), SIGNAL(fetchedGamingDay(int)), this,
            SLOT(downloadDayResultsFinished(int)), Qt::QueuedConnection);
    connect(parsers->getOperationByName("www.khl.ru-day"), SIGNAL(parsedGamingDay()), this,
            SLOT(parsingDayFinished()), Qt::QueuedConnection);
    connect(readers->getOperationByName("www.khl.ru-day"), SIGNAL(ReadingTodayResultsComplete()), this,
            SLOT(fillMatchesTodayTable()), Qt::QueuedConnection);
}

void presentation::proxySettingsChanged()
{
    qDebug();
    QNetworkProxy::setApplicationProxy(QNetworkProxy(((QNetworkProxy::ProxyType)(viewSettings->typeProxy())),
                                                     viewSettings->hostProxy(), viewSettings->portProxy(),
                                                     viewSettings->userProxy(), viewSettings->pwdProxy()) );
}

void presentation::downloadDayResultsFinished(int err)
{
    if (err == QNetworkReply::NoError)
    {
        qDebug()<<"Current day information downloaded. Start parser";
        view->setStatus(tr("Parsing downloaded matches info for current day : ") + view->selectedDay().toString("dd.MM.yy"));
        parsers->getOperationByName("www.khl.ru-day")->setDate(view->selectedDay());
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
    bool mayShowResults = readers->getOperationByName("www.khl.ru-day")->date() == view->selectedDay();
    //filtering by date
    if (mayShowResults)
    {
        view->setStatus(tr("States of current matches were updated"));
        qDebug()<<view->status();
        tableModel->clear();
        tableModel->setHorizontalHeaderLabels(QStringList() << tr("Home") << tr("Away") << tr("Count") << tr("State"));
        QStringList teams = ((IRWData*)(readers->getOperationByName("www.khl.ru-day")))->teams();
        QStringList counts = ((IRWData*)(readers->getOperationByName("www.khl.ru-day")))->counts();
        QStringList states = ((IRWData*)(readers->getOperationByName("www.khl.ru-day")))->states();
        qDebug()<<"Teams"<<":"<<teams;
        qDebug()<<"Counts"<<":"<<counts;
        qDebug()<<"States"<<":"<<states;
        int cteam = teams.count();
        for(int i = 0; i < cteam; ++i)
        {
            QList<QStandardItem*> row;
            qDebug() << "home" << ":" << (teams[i]).section("-", 0, 0);
            qDebug() << "away" << ":" << (teams[i]).section("-", 1, 1);
            QStandardItem* homeitem = new QStandardItem((teams[i]).section("-", 0, 0));
            QStandardItem* awayitem = new QStandardItem((teams[i]).section("-", 1, 1));


            QStandardItem* countitem = new QStandardItem(counts[i]);
            QStandardItem* stateitem = new QStandardItem(states[i]);
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
        view->resizeTable();
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

    bool mayShowResults = readers->getOperationByName("www.khl.ru")->date() == view->selectedDay();

    //Filtering by date
    if (mayShowResults)
    {
        view->setStatus(QString(tr("Matches for ") + view->selectedDay().toString("dd.MM.yy")));
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
        view->resizeTable();
    }

}

void presentation::EmptyReadingFile()
{
    qDebug() << "Sorry, empty reading file";
    //TODO: create question
    view->setStatus(tr("Downloading matches info for ") + view->selectedDay().toString("dd.MM.yy"));
    downloaders->getOperationByName("www.khl.ru")->setDate(view->selectedDay());
    runners->startRunnerByName("www.khl.ru-downloader");
}

void presentation::gamingDaySelected(const QDate& gameDay)
{
    qDebug() << gameDay;
    view->setSelectedDay(gameDay);
    if ( gameDay != QDate::currentDate() )
    {
        qDebug()<<"Loading past information";
        qDebug()<<"Stopping update for current dat";
        runners->getRunner("www.khl.ru-downloader-day")->stopExec();
        readers->getOperationByName("www.khl.ru")->setDate(view->selectedDay());
        runners->startRunnerByName("www.khl.ru-reader");
    }
    else
    {
        qDebug()<<"Loading current info";
        view->setStatus(tr("Downloading match info for current day ") + view->selectedDay().toString("dd.MM.yy"));
        downloaders->getOperationByName("www.khl.ru-day")->setDate(view->selectedDay());
        runners->startRunnerByName("www.khl.ru-downloader-day");
    }
}

void presentation::downloadMonthResultsFinished(int error)
{
    if (error == QNetworkReply::NoError)
    {
        qDebug() << "Download successfully finished. Start parsing";
        view->setStatus(tr("Parsing downloaded matches info for ") + view->selectedDay().toString("dd.MM.yy"));
        parsers->getOperationByName("www.khl.ru")->setDate(view->selectedDay());
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
    readers->getOperationByName("www.khl.ru")->setDate(view->selectedDay());
    runners->startRunnerByName("www.khl.ru-reader");
}

void presentation::parsingDayFinished()
{
     qDebug() << "Parsing successfully finished. Start reading.";
     readers->getOperationByName("www.khl.ru-day")->setDate(view->selectedDay());
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
