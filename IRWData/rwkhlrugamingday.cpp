#include <QDir>
#include <QBuffer>
#include <QtXmlPatterns/QXmlQuery>
#include <QtXmlPatterns/QXmlFormatter>

#include "constants.h"
#include "constants_downloader.h"
#include "rwkhlrugamingday.h"

void RWKhlRuGamingDay::run()
{
    //TODO!!
    qDebug() << QTime::currentTime() << ":" << QThread::currentThreadId()<<"Date: "<<date().toString("dd.MM.yy").toAscii();
    setSavedParsedFilename();
    QStringList teams = QStringList();
    QStringList counts = QStringList();
    QFile *source =  new QFile(savedParsedFile);
    //Open query file:Read teams
    teams  = getDataFromParsedXML(source, ":reading/Resources/requests/getmatchesforday.xq");
    counts = getDataFromParsedXML(source, ":reading/Resources/requests/getcountmatchesforday.xq");
    qDebug()<<teams;
    qDebug()<<counts;

    setTeams(teams);
    setCounts(counts);
    emit ReadingComplete();
    emit endOperation();
}


QStringList RWKhlRuGamingDay::getDataFromParsedXML(QFile *source, const QString &resfname)
{
    QFile queryFile(resfname);
    QStringList retList = QStringList();
    if (source->open(QIODevice::ReadOnly))
    {
        if (queryFile.open(QIODevice::ReadOnly))
        {
            qDebug()<<"Query file opened";
            QString request = queryFile.readAll();
            QXmlQuery xmlQuery;
            xmlQuery.bindVariable("document", source);
            xmlQuery.bindVariable("date", QXmlItem(date().toString("dd.MM.yy")));
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
    }
    else
    {
        emit FileNotExistToReading();
    }
    return retList;
}

void RWKhlRuGamingDay::setSavedParsedFilename()
{
    qDebug() << QTime::currentTime() << ":" << QThread::currentThreadId();
    qDebug() << "Date:" << date();
    savedParsedFile =  QString(QDir::currentPath() + "/" + ResTmpParsePath + KhlRuName + GameMonth);
    qDebug() << "tmpFname:" << savedParsedFile;
    foreach(Season season , seasons)
    {
        if (isRegular(date(), season) || isPlayOffs(date(), season))
        {

            savedParsedFile += QString::number(season.yearStart) + "-" + QString::number(season.yearEnd) + "/" +
                               QString::number(date().month()) + ".xml";
            break;
        }
    }
    qDebug() << "Saved parsed filename" << ":" << savedParsedFile;
}
