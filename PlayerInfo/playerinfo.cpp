
#include "playerinfo.h"

PlayerInfo::PlayerInfo(QObject* parent):
    QObject(parent)
{
    _playerName = "Unknown";
    _playerNumber = -1;
    _commandName = "Unknown";
    _bornDate = QDate(1900, 1, 1);
    _role = norole;
    _weight = -1;
    _growth = -1;
}

QString PlayerInfo::playerName() const
{
    return _playerName;
}

void PlayerInfo::setPlayerName(const QString& copyName)
{
    _playerName = copyName;
}

int PlayerInfo::playerNumber() const
{
    return _playerNumber;
}

void PlayerInfo::setPlayerNumber(int copyNumber)
{
    _playerNumber = copyNumber;
}

QString PlayerInfo::commandName() const
{
    return _commandName;
}

void PlayerInfo::setCommandName(const QString& copyCommandName)
{
    _commandName = copyCommandName;
}

QDate PlayerInfo::bornDate() const
{
    return _bornDate;
}

void PlayerInfo::setBornDate(const QDate& copyBornDate)
{
    _bornDate = copyBornDate;
}

PlayingRoles PlayerInfo::role() const
{
    return _role;
}

void PlayerInfo::setRole(PlayingRoles copyRole)
{
    _role = copyRole;
}

int PlayerInfo::weight() const
{
    return _weight;
}

void PlayerInfo::setWeight(int copyWeight)
{
    _weight = copyWeight;
}

int PlayerInfo::growth() const
{
    return _growth;
}

void PlayerInfo::setGrowth(int copyGrowth)
{
    _growth = copyGrowth;
}

