#include <QDir>

#include "constants.h"
#include "constants_downloader.h"
#include "rwkhlrugamingday.h"

void RWKhlRuGamingDay::run()
{
    qDebug() << QTime::currentTime() << ":" << QThread::currentThreadId();
    setSavedParsedFilename();
    QFile source(savedParsedFile);
    if(source.open(QIODevice::ReadOnly))
    {

    }
    else
    {
        emit FileNotExistToReading();
    }
    emit endOperation();
}

void RWKhlRuGamingDay::setSavedParsedFilename()
{
    qDebug() << QTime::currentTime() << ":" << QThread::currentThreadId();
    qDebug()<<"Date:"<<date();
    savedParsedFile =  QString(QDir::currentPath() + "/" + ResTmpParsePath + KhlRuName + GameMonth);
    qDebug()<<"tmpFname:"<<savedParsedFile;
    foreach(Season season , seasons)
    {
        if (isRegular(date(), season) || isPlayOffs(date(), season))
        {

            savedParsedFile += QString::number(season.yearStart) + "-" + QString::number(season.yearEnd) + "/" +
                             QString::number(date().month()) + ".xml";
            break;
        }
    }
    qDebug()<<"Saved parsed filename"<<":"<<savedParsedFile;
}
