#include <QFile>
#include <QtXmlPatterns/QXmlQuery>
#include <QtXmlPatterns/QXmlFormatter>
#include <QDir>

#include "parserkhlrugamingday.h"
#include "constants_downloader.h"

void ParserKhlRuGamingDay::run()
{
    qDebug() << QTime::currentTime() << ":" << QThread::currentThreadId();
    setFilenameForParsing();
    //Open query file
    QFile queryFile(QString(":parsing/Resources/requests/getcurrentdaymatches.xq"));
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

    emit parsedGamingDay();
    emit endOperation();
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
