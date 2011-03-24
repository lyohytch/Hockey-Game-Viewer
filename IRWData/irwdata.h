#ifndef IRWDATA_H
#define IRWDATA_H

#include <QRunnable>
#include <QObject>

class IRWData : public QObject, public QRunnable
{
        Q_OBJECT
        Q_PROPERTY(QString type READ type)
    public:
        explicit IRWData(QObject* parent = 0, const QString& typeName = 0): QObject(parent), _type(typeName) {}

        QString type() const
        {
            return _type;
        }
        //void writeData() = 0;
    signals:

    public slots:
    private:
        QString _type;
};

#endif // IRWDATA_H
