#ifndef IRWDATA_H
#define IRWDATA_H
#include <QStringList>

#include "ioperation.h"

class IRWData : public IOperation
{
        Q_OBJECT
        Q_PROPERTY(QStringList teams READ teams WRITE setTeams)
        Q_PROPERTY(QStringList counts READ counts WRITE setCounts)
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

    signals:
        void FileNotExistToReading();
        void ReadingComplete();
    protected slots:
        void setTeams(const QStringList &copyTeams)
        {
            _teams = copyTeams;
        }
        void setCounts(const QStringList &copyCounts)
        {
            _counts = copyCounts;
        }

    private:
        QStringList _teams;
        QStringList _counts;

};

#endif // IRWDATA_H
