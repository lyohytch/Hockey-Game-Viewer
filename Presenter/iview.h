#ifndef IVIEW_H
#define IVIEW_H

#include <QMainWindow>
#include <QTableView>
#include <QCalendarWidget>
#include <QDate>

class IView : public QMainWindow
{
        Q_OBJECT

        Q_PROPERTY(QString downloaderName READ downloaderName WRITE setdownloaderName)

        Q_PROPERTY(int typeProxy READ  typeProxy WRITE setTypeProxy)
        Q_PROPERTY(QString hostProxy READ hostProxy WRITE setHostProxy)
        Q_PROPERTY(int portProxy READ portProxy WRITE setPortProxy)
        Q_PROPERTY(QString userProxy READ userProxy WRITE setUserProxy)
        Q_PROPERTY(QString pwdProxy READ pwdProxy WRITE setPwdProxy)

        Q_PROPERTY(QTableView *table READ table WRITE setTable)
        Q_PROPERTY(QCalendarWidget *calendar READ calendar WRITE setCalendar)
    public:
        IView(QWidget* parent = 0) : QMainWindow(parent) {}
        virtual ~IView() {}
        QString downloaderName() const
        {
            return _downloaderName;
        }

        int typeProxy() const
        {
            return _typeProxy;
        }
        QString hostProxy()const
        {
            return _hostProxy;
        }
        int portProxy() const
        {
            return _portProxy;
        }
        QString userProxy() const
        {
            return _userProxy;
        }
        QString pwdProxy() const
        {
            return _pwdProxy;
        }

        QTableView *table() const
        {
            return _table;
        }

        QCalendarWidget *calendar() const
        {
            return _calendar;
        }

    signals:
        void GamingDaySelected(const QDate& gameDate);
    public slots:
        void setdownloaderName(const QString& copySite)
        {
            _downloaderName = copySite;
        }

        void setTypeProxy(int type)
        {
            _typeProxy = type;
        }
        void setHostProxy(const QString& host)
        {
            _hostProxy = host;
        }
        void setPortProxy(int port)
        {
            _portProxy = port;
        }
        void setUserProxy(const QString& user)
        {
            _userProxy = user;
        }
        void setPwdProxy(const QString& pwd)
        {
            _pwdProxy = pwd;
        }

        void setTable(QTableView *copyTable)
        {
            _table = copyTable;
        }
        void setCalendar(QCalendarWidget *copyCalendar)
        {
            _calendar = copyCalendar;
        }


    private:
        QString _downloaderName;

        int _typeProxy;
        QString _hostProxy;
        int _portProxy;
        QString _userProxy;
        QString _pwdProxy;

        QTableView *_table;
        QCalendarWidget *_calendar;
};

#endif // IVIEW_H
