#include "match.h"

Match::Match(QObject* parent):
    QObject(parent)
{
    _date = QDate(1900, 1, 1);
    _time = QTime(0, 0, 0, 0);
    _country = "Unknown";
    _city = "Unknown";
    _home = 0;
    _away = 0;
    _scoreHome = -1;
    _scoreAway = -1;
    _state = NotStarted;
    _periodGameTime = QTime(0, 0, 0, 0);
    _matchTime = QTime(0, 0, 0, 0);
}

QDate Match::date() const
{
    return _date;
}

void Match::setDate(const QDate& copyDate)
{
    _date = copyDate;
}

QTime Match::time() const
{
    return _time;
}

void Match::setTime(const QTime& copyTime)
{
    _time = copyTime;
}

QString Match::country() const
{
    return _country;
}

void Match::setCountry(const QString& copyCountry)
{
    _country = copyCountry;
}

QString Match::city() const
{
    return _city;
}

void Match::setCity(const QString& copyCity)
{
    _city = copyCity;
}

CommandInfo* Match::home() const
{
    return _home;
}

void Match::setHome(CommandInfo* copyHome)
{
    _home = copyHome;
}

CommandInfo* Match::away() const
{
    return _away;
}

void Match::setAway(CommandInfo* copyAway)
{
    _away = copyAway;
}

int Match::scoreHome() const
{
    return _scoreHome;
}

void Match::setScoreHome(int copyScoreHome)
{
    _scoreHome = copyScoreHome;
}

int Match::scoreAway() const
{
    return _scoreAway;
}

void Match::setScoreAway(int copyScoreAway)
{
    _scoreAway = copyScoreAway;
}

GameState Match::state() const
{
    return _state;
}

void Match::setState(GameState copyState)
{
    _state = copyState;
}

QTime Match::periodGameTime() const
{
    return _periodGameTime;
}

void Match::setPeriodGameTime(const QTime& copyPeriodGameTime)
{
    _periodGameTime = copyPeriodGameTime;
}

QTime Match::matchTime() const
{
    return _matchTime;
}

void Match::setMatchTime(const QTime& copyMatchTime)
{
    _matchTime = copyMatchTime;
}

