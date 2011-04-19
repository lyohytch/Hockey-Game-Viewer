#ifndef IOPERATION_H
#define IOPERATION_H

#include <QObject>
#include <QDate>

class IOperation : public QObject
{
        Q_OBJECT
        Q_PROPERTY(QString targetSite READ targetSite)
        Q_PROPERTY(long interval READ interval WRITE setInterval)
        Q_PROPERTY(QDate date READ date WRITE setDate)
    public:
        explicit IOperation(QObject* parent = 0, const QString& siteName = 0): QObject(parent), _targetSite(siteName) {}
        virtual ~IOperation() {}

        QDate date() const
        {
            return _date;
        }

        QString targetSite() const
        {
            return _targetSite;
        }
        long interval() const
        {
            return _interval;
        }
        virtual void run() = 0;
    signals:
        void endOperation();
    public slots:
       void setInterval(long copyInterval)
       {
           _interval = copyInterval;
       }

       void setDate(QDate copyDate)
       {
           _date = copyDate;
       }

    private:
        QString _targetSite;
        long _interval;
        QDate _date;
};
#endif // IOPERATION_H
