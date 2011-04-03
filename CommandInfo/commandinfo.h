#ifndef COMMANDINFO_H
#define COMMANDINFO_H
#include <QObject>

#include "playerinfo.h"


class  CommandInfo : public QObject
{
        Q_OBJECT
        Q_PROPERTY(QString commandName READ commandName WRITE setCommandName)
        Q_PROPERTY(QString countryName READ countryName WRITE setCountryName)
        Q_PROPERTY(QString cityName READ cityName WRITE setCityName)
        Q_PROPERTY(QList<PlayerInfo*> players READ players WRITE setPlayers)
        Q_PROPERTY(QString division READ division WRITE setDivision)
        Q_PROPERTY(QString conference READ conference WRITE setConference)
    public:
        CommandInfo(QObject* parent = 0);
        QString commandName() const;
        QString countryName() const;
        QString cityName() const;
        QList<PlayerInfo*> players() const;
        QString division() const;
        QString conference() const;
    public slots:
        void setCommandName(const QString& copyCommandName);
        void setCountryName(const QString& copyCountryName);
        void setCityName(const QString& copyCityName);
        void setPlayers(const QList<PlayerInfo*> &copyPlayers);
        void setDivision(const QString& copyDivision);
        void setConference(const QString& copyConference);
    private:
        QString _commandName;
        QString _countryName;
        QString _cityName;
        QList<PlayerInfo*> _players;
        QString _division;
        QString _conference;
};


#endif // COMMANDINFO_H
