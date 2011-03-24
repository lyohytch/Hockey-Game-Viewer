#ifndef DOWNLOADERKHLRU_H
#define DOWNLOADERKHLRU_H

#include <QThread>
#include <QDateTime>

#include "constants.h"
#include "idownloader.h"

class DownloaderKhlRu : public IDownloader
{
        Q_OBJECT
    public:
        explicit DownloaderKhlRu(QObject* parent = 0, const QString& siteName = "www.khl.ru") : IDownloader(parent, siteName)
        {
            setInterval(20000);
        }
        virtual ~DownloaderKhlRu() {}
        virtual void fetchGamingMonth()
        {
            qDebug();
        }
        virtual void fetchGamingDay()
        {
            qDebug();
        }
        virtual void fetchMatch(const QString& home, const QString& away)
        {
            Q_UNUSED(home);
            Q_UNUSED(away);
            qDebug();
        }
        virtual void fetchCommand(const QString& commandName)
        {
            Q_UNUSED(commandName);
            qDebug();
        }
        virtual void fetchPlayer(const QString& playerName)
        {
            Q_UNUSED(playerName);
            qDebug();
        }
        virtual void run()
        {
            qDebug() << QTime::currentTime() << ":" << QThread::currentThreadId();
            emit finish();
        }

    signals:
};

#endif // DOWNLOADERKHLRU_H
