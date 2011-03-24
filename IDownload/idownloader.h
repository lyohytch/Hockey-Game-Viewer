#ifndef IDOWNLOADER_H
#define IDOWNLOADER_H

#include <QDate>
#include "ioperation.h"

class IDownloader : public IOperation
{
        Q_OBJECT

        Q_PROPERTY(QDate date READ date WRITE setDate)
    public:
        explicit IDownloader(QObject* parent = 0, const QString& siteName = 0): IOperation(parent, siteName) {}

        virtual ~IDownloader() {}

        QDate date() const
        {
            return _date;
        }

        virtual void fetchGamingMonth() = 0;
        virtual void fetchGamingDay() = 0;
        virtual void fetchMatch(const QString& home, const QString& away) = 0;
        virtual void fetchCommand(const QString& commandName) = 0;
        virtual void fetchPlayer(const QString& playerName) = 0;
    signals:
        void GamingMonthFetched(const QStringList& urlContent);
        void GamingDayFetched(const QString& urlContent);
        void MatchFetched(const QString& urlContent);
        void CommandFetched(const QString& urlContent);
        void PlayerFetched(const QString& fetched);
        void finish();
    public slots:
        void setDate(const QDate& copyDate)
        {
            _date = copyDate;
        }
    private:
        QDate _date;

};

#endif // IDOWNLOADER_H
