#include "commandinfo.h"

CommandInfo::CommandInfo(QObject* parent):
    QObject(parent)
{
    _commandName = "Unknown";
    _countryName = "Unknown";
    _cityName = "Unknown";
}
QString CommandInfo::commandName() const
{
    return _commandName;
}

void CommandInfo::setCommandName(const QString& copyCommandName)
{
    _commandName = copyCommandName;
}

QString CommandInfo::countryName() const
{
    return _countryName;
}

void CommandInfo::setCountryName(const QString& copyCountryName)
{
    _countryName = copyCountryName;
}

QString CommandInfo::cityName() const
{
    return _cityName;
}

void CommandInfo::setCityName(const QString& copyCityName)
{
    _cityName = copyCityName;
}

QList<PlayerInfo*> CommandInfo::players() const
{
    return _players;
}

void CommandInfo::setPlayers(const QList<PlayerInfo*> &copyPlayers)
{
    _players = copyPlayers;
}

QString CommandInfo::division() const
{
    return _division;
}

void CommandInfo::setDivision(const QString& copyDivision)
{
    _division = copyDivision;
}

QString CommandInfo::conference() const
{
    return _conference;
}

void CommandInfo::setConference(const QString& copyConference)
{
    _conference = copyConference;
}

