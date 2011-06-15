#include <QFile>
#include <QtXmlPatterns/QXmlQuery>
#include <QtXmlPatterns/QXmlFormatter>

#include "p_common.h"
#include "constants.h"

void ParserKhlRu::parseDownloadedFile(const QString& parseFPath)
{
    //Open query file
    QFile queryFile(parseFPath);
    if (queryFile.open(QIODevice::ReadOnly))
    {
        qDebug() << "Query file opened";
        QString request = queryFile.readAll();
        QFile file(savedFilename);
        if (file.open(QIODevice::ReadOnly))
        {
            QFile output(parsedFilename);
            if (output.open(QIODevice::ReadWrite))
            {
                QXmlQuery xmlQuery;
                qDebug() << "File opened";
                xmlQuery.bindVariable("document", &file);
                xmlQuery.setQuery(request);
                if (!xmlQuery.isValid())
                {
                    qDebug() << "Query isn't valid";
                }
                QXmlFormatter formatter(xmlQuery, &output);
                if (!xmlQuery.evaluateTo(&formatter))
                {
                    qDebug() << "Query can not evaluate!!";
                }
                output.close();
            }
            else
            {
                qDebug() << "Can not open file for writing parsed data";
            }
            file.close();
        }
        else
        {
            qDebug() << "Can't open source file";
        }
    }
    else
    {
        qDebug() << "Can't open resource file";
    }
}

void ParserKhlRu::finishTask()
{
    emit endOperation();
}

void ParserKhlRu::executeParsingProcess(const QString& parseFPath)
{
    qDebug() << QTime::currentTime() << ":" << QThread::currentThreadId();
    setFilenameForParsing();
    parseDownloadedFile(parseFPath);
    finishTask();
}
