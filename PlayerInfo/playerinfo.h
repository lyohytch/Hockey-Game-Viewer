#ifndef PLAYERINFO_H
#define PLAYERINFO_H
#include <QObject>
#include <QDate>

enum PlayingRoles
{
    norole = -1,
    goalkeeper = 0,
    forward = 1,
    defender = 2
};

class PlayerInfo : public QObject
{
        Q_OBJECT

        Q_PROPERTY(QString playerName READ playerName WRITE setPlayerName)
        Q_PROPERTY(int playerNumber READ playerNumber WRITE setPlayerNumber)
        Q_PROPERTY(QString commandName READ commandName WRITE setCommandName)
        Q_PROPERTY(QDate bornDate READ bornDate WRITE setBornDate)
        Q_PROPERTY(PlayingRoles role READ role WRITE setRole)
        Q_PROPERTY(int weight READ weight WRITE setWeight)
        Q_PROPERTY(int growth READ growth WRITE setGrowth)
        Q_ENUMS(PlayingRoles)
    public:
        PlayerInfo(QObject* parent = 0);
        QString playerName() const;
        int playerNumber() const;
        QString commandName() const;
        QDate bornDate() const;
        PlayingRoles role() const;
        int weight() const;
        int growth() const;
    public slots:
        void setPlayerName(const QString& copyName);
        void setPlayerNumber(int copyNumber);
        void setCommandName(const QString& copyCommandName);
        void setBornDate(const QDate& copyBornDate);
        void setRole(PlayingRoles copyRole);
        void setWeight(int copyWeight);
        void setGrowth(int copyGrowth);
    private:
        QString _playerName;
        int _playerNumber;
        QString _commandName;
        QDate _bornDate;
        PlayingRoles _role;
        int _weight;
        int _growth;

};

#endif // PLAYERINFO_H
