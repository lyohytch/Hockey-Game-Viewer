#ifndef GAMINGDAY_H
#define GAMINGDAY_H
#include <QObject>
#include <QDate>
#include <QList>

#include "match.h"
namespace gameday
{
    typedef match::Match Match;

    enum DayOfWeek
    {
        None = -1,
        Monday = 1,
        Tuesday = 2,
        Wednesday = 3,
        Thursday = 4,
        Friday = 5,
        Saturday = 6,
        Sunday = 7
    };

    class  GamingDay : public QObject
    {
            Q_OBJECT
            Q_PROPERTY(QDate date READ date WRITE setDate)
            Q_PROPERTY(DayOfWeek dayOfWeek READ dayOfWeek WRITE setDayOfWeek)
            Q_PROPERTY(QList<Match *> matches READ matches WRITE setMatches)
            Q_ENUMS(DayOfWeek)
        public:
            GamingDay(QObject *parent = 0);
            QDate date() const;
            DayOfWeek dayOfWeek() const;
            QList<Match *> matches() const;
        public slots:
            void setDate(const QDate &copyDate);
            void setDayOfWeek(DayOfWeek copyDayOfWeek);
            void setMatches(const QList<Match *> &copyMatches);
    private:
            QDate _date;
            DayOfWeek _dayOfWeek;
            QList<Match *> _matches;
    };
}

#endif // GAMINGDAY_H
