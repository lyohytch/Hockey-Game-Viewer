#include "gamingday.h"

namespace gameday
{
    GamingDay::GamingDay(QObject *parent):
            QObject(parent)
    {
        _date = QDate(1900, 1, 1);
        _dayOfWeek = gameday::None;
    }

    QDate GamingDay::date() const
    {
        return _date;
    }

    void GamingDay::setDate(const QDate &copyDate)
    {
        _date = copyDate;
    }

    DayOfWeek GamingDay::dayOfWeek() const
    {
        return _dayOfWeek;
    }

    void GamingDay::setDayOfWeek(DayOfWeek copyDayOfWeek)
    {
        _dayOfWeek = copyDayOfWeek;
    }

    QList<Match *> GamingDay::matches() const
    {
        return _matches;
    }

    void GamingDay::setMatches(const QList<Match *> &copyMatches)
    {
        _matches = copyMatches;
    }
}
