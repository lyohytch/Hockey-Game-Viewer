#ifndef IRWDATA_H
#define IRWDATA_H
#include <QStringList>

#include "ioperation.h"

class IRWData : public IOperation
{
        Q_OBJECT
        Q_PROPERTY(QStringList teams READ teams WRITE setTeams)
        Q_PROPERTY(QStringList counts READ counts WRITE setCounts)
        Q_PROPERTY(QStringList states READ states WRITE setStates)
    public:
        explicit IRWData(QObject* parent = 0, const QString& typeName = 0): IOperation(parent, typeName) {}
        QStringList teams()
        {
            return _teams;
        }
        QStringList counts()
        {
            return _counts;
        }
        QStringList states()
        {
            return _states;
        }

    signals:
        void FileNotExistToReading();
        void ReadingAnyDayComplete();
        void ReadingTodayResultsComplete();
    protected slots:
        void setTeams(const QStringList &copyTeams)
        {
            _teams = copyTeams;
        }
        void setCounts(const QStringList &copyCounts)
        {
            _counts = copyCounts;
        }
        void setStates(const QStringList &copyStates)
        {
            _states = copyStates;
        }

    private:
        QStringList _teams;
        QStringList _counts;
        QStringList _states;

};

#endif // IRWDATA_H
