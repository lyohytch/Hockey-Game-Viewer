#ifndef MATCH_H
#define MATCH_H
#include <QObject>
#include <QDateTime>

#include "commandinfo.h"

namespace match
{
    typedef command::CommandInfo CommandInfo;

    enum GameState
    {
        NotStarted = -1,
        TimeOut = 0,
        First  = 1,
        Second = 2,
        Third = 3,
        Overtime = 4,
        Bullits = 5,
        Ended = 6,
    };

    class Match : public QObject
    {
            Q_OBJECT
            Q_PROPERTY(QDate date READ date WRITE setDate)
            Q_PROPERTY(QTime time READ time WRITE setTime)
            Q_PROPERTY(QString country READ country WRITE setCountry)
            Q_PROPERTY(QString city READ city WRITE setCity)
            Q_PROPERTY(CommandInfo* home READ home WRITE setHome)
            Q_PROPERTY(CommandInfo* away READ away WRITE setAway)
            Q_PROPERTY(int scoreHome READ scoreHome WRITE setScoreHome)
            Q_PROPERTY(int scoreAway READ scoreAway WRITE setScoreAway)
            Q_PROPERTY(GameState state READ state WRITE setState NOTIFY stateChanged)
            Q_PROPERTY(QTime periodGameTime READ periodGameTime WRITE setPeriodGameTime)
            Q_PROPERTY(QTime matchTime READ matchTime WRITE setMatchTime)
            Q_ENUMS(GameState)
        public:

            Match(QObject* parent = 0);
            QDate date() const;
            QTime time() const;
            QString country() const;
            QString city() const;
            CommandInfo* home() const;
            CommandInfo* away() const;
            int scoreHome() const;
            int scoreAway() const;
            GameState state() const;
            QTime periodGameTime() const;
            QTime matchTime() const;
        public slots:
            void setDate(const QDate& copyDate);
            void setTime(const QTime& copyTime);
            void setCountry(const QString& copyCountry);
            void setCity(const QString& copyCity);
            void setHome(CommandInfo* copyHome);
            void setAway(CommandInfo* copyAway);
            void setScoreHome(int copyScoreHome);
            void setScoreAway(int copyScoreAway);
            void setState(GameState copyState);
            void setPeriodGameTime(const QTime& copyPeriodGameTime);
            void setMatchTime(const QTime& copyMatchTime);
        private:
            QDate _date;
            QTime  _time;
            QString _country;
            QString _city;
            CommandInfo* _home;
            CommandInfo* _away;
            int _scoreHome;
            int _scoreAway;
            GameState _state;
            QTime _periodGameTime;
            QTime _matchTime;
        signals:
         void stateChanged(GameState newState);
    };
}

#endif // MATCH_H
