#ifndef IVIEW_H
#define IVIEW_H

#include <QTableView>
#include <QDateEdit>
#include <QDate>

class IView : public QObject
{
        Q_OBJECT

        Q_PROPERTY(QString downloaderName READ downloaderName WRITE setdownloaderName)

        Q_PROPERTY(QTableView *table READ table WRITE setTable)
        Q_PROPERTY(QDateEdit *calendar READ calendar WRITE setCalendar)

        Q_PROPERTY(QString status READ status WRITE setStatus NOTIFY SetStatusOnForm)
    public:
        IView(QObject* parent = 0) : QObject(parent) {}
        virtual ~IView() {}
        QString downloaderName() const
        {
            return _downloaderName;
        }

        QTableView *table() const
        {
            return _table;
        }

        QDateEdit *calendar() const
        {
            return _calendar;
        }

        QString status() const
        {
            return _status;
        }

        virtual void gamingDaySelected(const QDate & gameDate) = 0;

    signals:
        void GamingDaySelected(const QDate& gameDate);
        void SetStatusOnForm(const QString &status);
    public slots:
        void setdownloaderName(const QString& copySite)
        {
            _downloaderName = copySite;
        }


        void setTable(QTableView *copyTable)
        {
            _table = copyTable;
        }
        void setCalendar(QDateEdit *copyCalendar)
        {
            _calendar = copyCalendar;
        }

        void setStatus(const QString &copyStatus)
        {
            _status = copyStatus;
            emit SetStatusOnForm(_status);
        }

    private:
        QString _downloaderName;

        QTableView *_table;
        QDateEdit *_calendar;

        QString _status;
};
#endif // IVIEW_H
