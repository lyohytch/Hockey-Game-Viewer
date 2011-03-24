#ifndef PARSERKHLRU_H
#define PARSERKHLRU_H

#include <QObject>
#include <QDateTime>
#include <QThread>

#include "iparser.h"
#include "constants.h"

class ParserKhlRu : public IParser
{
        Q_OBJECT
    public:
        explicit ParserKhlRu(QObject* parent = 0, const QString& targetName = "www.khl.ru") : IParser(parent, targetName)
        {
           setInterval(10000);
        }
        virtual void run()
        {
            qDebug() << QTime::currentTime() << ":" << QThread::currentThreadId();
        }

    signals:

};

#endif // PARSERKHLRU_H
