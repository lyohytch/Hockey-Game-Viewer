#include <QFile>
#include <QDir>

#include "p_onlinematches.h"
#include "constants_downloader.h"

void ParserKhlRuGamingDay::run()
{
    executeParsingProcess(":parsing/Resources/requests/getcurrentdaymatches.xq");
}

void ParserKhlRuGamingDay::finishTask()
{
    emit parsedGamingDay();
    ParserKhlRu::finishTask();
}

void ParserKhlRuGamingDay::setFilenameForParsing()
{
    qDebug() << QTime::currentTime() << ":" << QThread::currentThreadId();
    qDebug()<<"Date:"<<date();
    savedFilename = QString(QDir::currentPath() + "/" + ResTmpDownloadPath + KhlRuName + CurrentGameDay + "current.html");
    parsedDir =  QString(QDir::currentPath() + "/" + ResTmpParsePath + KhlRuName + CurrentGameDay);
    parsedFilename = QString(parsedDir + "current.xml");

    qDebug()<<"Source filename"<<":"<<savedFilename;
    qDebug()<<"Parsed filename"<<":"<<parsedFilename;
    QDir dir(parsedDir);
    if (!dir.exists())
    {
        qDebug() << "Dir isn't exist ";
        dir.mkpath(parsedDir);
    }
}
