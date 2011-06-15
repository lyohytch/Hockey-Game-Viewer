#include <QDir>
#include <QBuffer>

#include "p_pastmatches.h"
#include "constants_downloader.h"
//#include "gamingday.h"
//TODO: можно объединить реализации для онлайн и прошлых матчей

void ParseKhlRuGamingMonth::run()
{
    executeParsingProcess(":parsing/Resources/requests/gamingmonth.xq");
}

void ParseKhlRuGamingMonth::finishTask()
{
    emit parsedGamingMonth();
    ParserKhlRu::finishTask();
}

void ParseKhlRuGamingMonth::setFilenameForParsing()
{
    qDebug() << QTime::currentTime() << ":" << QThread::currentThreadId();
    qDebug()<<"Date:"<<date();
    savedFilename = QString(QDir::currentPath() + "/" + ResTmpDownloadPath + KhlRuName + GameMonth);
    parsedFilename =  QString(QDir::currentPath() + "/" + ResTmpParsePath + KhlRuName + GameMonth);
    parsedDir = QString(parsedFilename);
    qDebug()<<"tmpFname:"<<savedFilename;
    foreach(Season season , seasons)
    {
        if (isRegular(date(), season) || isPlayOffs(date(), season))
        {

            savedFilename += QString::number(season.yearStart) + "-" + QString::number(season.yearEnd) + "/" +
                             QString::number(date().month()) + ".html";
            parsedFilename += QString::number(season.yearStart) + "-" + QString::number(season.yearEnd) + "/" +
                             QString::number(date().month()) + ".xml";
            parsedDir += QString::number(season.yearStart) + "-" + QString::number(season.yearEnd) + "/";
            break;
        }
    }
    qDebug()<<"Source filename"<<":"<<savedFilename;
    qDebug()<<"Parsed filename"<<":"<<parsedFilename;
    QDir dir(parsedDir);
    if (!dir.exists())
    {
        qDebug() << "Dir isn't exist ";
        dir.mkpath(parsedDir);
    }
}
