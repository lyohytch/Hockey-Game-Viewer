#ifndef DOWNLOADERKHLRU_H
#define DOWNLOADERKHLRU_H

#include "constants.h"
#include "idownloader.h"

class DownloaderKhlRu : public IDownloader
{
        Q_OBJECT
    public:
        explicit DownloaderKhlRu(QObject* parent = 0, const QString& siteName = "www.khl.ru") : IDownloader(parent, siteName) {}
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

        virtual void run ()
        {
            qDebug();
        }

    signals:

    public slots:

};

#endif // DOWNLOADERKHLRU_H
