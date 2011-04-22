#include <QDir>
#include <QtXmlPatterns/QXmlQuery>
#include <QtXmlPatterns/QXmlFormatter>
#include <QBuffer>

#include "pastmatches.h"
#include "constants_downloader.h"
//#include "gamingday.h"
//TODO: можно объединить реализации для онлайн и прошлых матчей

void ParseKhlRuGamingMonth::run()
{
    qDebug() << QTime::currentTime() << ":" << QThread::currentThreadId();
    setFilenameForParsing();
    //Open query file
    QFile queryFile(QString(":parsing/Resources/requests/gamingmonth.xq"));
    if (queryFile.open(QIODevice::ReadOnly))
    {
        qDebug()<<"Query file opened";
        QString request = queryFile.readAll();
        QFile file(savedFilename);
        if(file.open(QIODevice::ReadOnly))
        {
            QFile output(parsedFilename);
            if ( output.open(QIODevice::ReadWrite) )
            {
                QXmlQuery xmlQuery;
                qDebug()<<"File opened";
                xmlQuery.bindVariable("document", &file);
                xmlQuery.setQuery(request);
                if( !xmlQuery.isValid())
                {
                    qDebug()<<"Query isn't valid";
                }
                QXmlFormatter formatter(xmlQuery, &output);
                if( !xmlQuery.evaluateTo(&formatter))
                {
                    qDebug()<<"Query can not evaluate!!";
                }
                output.close();
            }
            else
            {
                qDebug()<<"Can not open file for writing parsed data";
            }
            file.close();
        }
        else
        {
            qDebug()<<"Can't open source file";
        }
    }
    else
    {
        qDebug()<<"Can't open resource file";
    }

    emit parsedGamingMonth();
    emit endOperation();
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
