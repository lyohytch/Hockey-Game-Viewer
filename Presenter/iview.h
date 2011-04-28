#ifndef IVIEW_H
#define IVIEW_H

#include <QAbstractItemModel>
#include <QDate>

class IView : public QObject
{
        Q_OBJECT

        Q_PROPERTY(QString status READ status WRITE setStatus NOTIFY SetStatusOnForm)
        Q_PROPERTY(QDate selectedDay READ selectedDay WRITE setSelectedDay)
    public:
        IView(QObject* parent = 0) : QObject(parent) {}
        virtual ~IView() {}
        QString downloaderName() const
        {
            return _downloaderName;
        }

        QString status() const
        {
            return _status;
        }

        QDate selectedDay() const
        {
            return _selectedDay;
        }
        virtual void gamingDaySelected(const QDate & gameDate) = 0;
        virtual void setModel(QAbstractItemModel *model) = 0;
        virtual void resizeTable() = 0;
    signals:
        void GamingDaySelected(const QDate& gameDate);
        void SetStatusOnForm(const QString &status);
    public slots:
        void setdownloaderName(const QString& copySite)
        {
            _downloaderName = copySite;
        }

        void setStatus(const QString &copyStatus)
        {
            _status = copyStatus;
            emit SetStatusOnForm(_status);
        }

        void setSelectedDay(const QDate &copydate)
        {
            _selectedDay = copydate;
        }

    private:
        QString _downloaderName;
        QString _status;
        QDate _selectedDay;
};
#endif // IVIEW_H
