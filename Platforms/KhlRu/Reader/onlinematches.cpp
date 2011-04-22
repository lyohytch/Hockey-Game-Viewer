#include <QDir>
#include <QBuffer>
#include <QtXmlPatterns/QXmlQuery>
#include <QtXmlPatterns/QXmlFormatter>

#include "constants.h"
#include "constants_downloader.h"
#include "onlinematches.h"

/*TODO: 1. Много времени до начала матча
          - Полей chet и chetmore расширенный нет
          - есть поле begin с некоторой инфой о матче
        2. Около 2 часов и менее до начала матча
          - Нет поля begin
          - Поля chet и chetmore есть
          - chet - показан статус ("Подготовка")
          - chetmore - то, что было до него в begin поле
        3. Матч идёт
        4. Матч закончился
 */
enum Fields
{
    TEAMS = 0,
    COUNTS,
    BEGIN,
    COMMENT = 3
};
void RWKhlRuGamingDay::run()
{
    //TODO!!
    qDebug() << QTime::currentTime() << ":" << QThread::currentThreadId()<<"Date: "<<date().toString("dd.MM.yy").toAscii();
    setSavedParsedFilename();
    QStringList teams = QStringList();
    QStringList counts = QStringList();
    QStringList states = QStringList();
    QFile *source =  new QFile(savedParsedFile);

    if (source && source->exists())
    {
        //Open query file:Read teams
        QStringList rawData  = getDataFromParsedXML(source, ":reading/Resources/requests/gettodaymatches.xq");
        for(int i = 0; i < rawData.count(); i = i + 4)
        {
            teams.append(rawData[i + TEAMS]);
            counts.append(rawData[i + COUNTS]);
            if (!QString(rawData[i+ BEGIN]).isEmpty())
            {
                states.append(rawData[i+BEGIN]);
            }
            else if ( !QString(rawData[i + COMMENT]).isEmpty() )
            {
                states.append(rawData[i + COMMENT]);
            }
        }
        qDebug()<<teams;
        qDebug()<<counts;

        setTeams(teams);
        setCounts(counts);
        setStates(states);
        emit ReadingTodayResultsComplete();
        emit endOperation();
    }
    else
    {
        emit FileNotExistToReading();
        emit endOperation();
    }
}

QStringList RWKhlRuGamingDay::getDataFromParsedXML(QFile *source, const QString &resfname)
{
    QFile queryFile(resfname);
    QStringList retList = QStringList();
    source->open(QIODevice::ReadOnly);
    if (queryFile.open(QIODevice::ReadOnly))
    {
        qDebug()<<"Query file opened";
        QString request = queryFile.readAll();
        QXmlQuery xmlQuery;
        xmlQuery.bindVariable("document", source);
        xmlQuery.setQuery(request);
        if( !xmlQuery.isValid())
        {
            qDebug()<<"Query isn't valid";
        }
        if( !xmlQuery.evaluateTo(&retList))
        {
             qDebug()<<"Query can not evaluate!!";
        }
        queryFile.close();
    }
    else
    {
        qDebug()<<"Can't open resource file";
    }
    source->close();
    return retList;
}

void RWKhlRuGamingDay::setSavedParsedFilename()
{
    qDebug() << QTime::currentTime() << ":" << QThread::currentThreadId();
    qDebug() << "Date:" << date();
    savedParsedFile =  QString(QDir::currentPath() + "/" + ResTmpParsePath + KhlRuName + CurrentGameDay + "current.xml");
    qDebug() << "Saved parsed filename" << ":" << savedParsedFile;
}
