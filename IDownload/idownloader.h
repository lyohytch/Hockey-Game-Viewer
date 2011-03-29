#ifndef IDOWNLOADER_H
#define IDOWNLOADER_H

#include <QDate>
#include <QtNetwork/QNetworkProxy>
#include <QtNetwork/QNetworkAccessManager>
#include <QtNetwork/QNetworkReply>
#include <QtNetwork/QNetworkRequest>

#include "ioperation.h"

class IDownloader : public IOperation
{
        Q_OBJECT

        Q_PROPERTY(QDate date READ date WRITE setDate)

        Q_PROPERTY(int typeProxy READ  typeProxy WRITE setTypeProxy)
        Q_PROPERTY(QString hostProxy READ hostProxy WRITE setHostProxy)
        Q_PROPERTY(int portProxy READ portProxy WRITE setPortProxy)
        Q_PROPERTY(QString userProxy READ userProxy WRITE setUserProxy)
        Q_PROPERTY(QString pwdProxy READ pwdProxy WRITE setPwdProxy)
    public:
        explicit IDownloader(QObject* parent = 0, const QString& siteName = 0): IOperation(parent, siteName)
        {
        }

        virtual ~IDownloader() {}

        QDate date() const
        {
            return _date;
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
    protected:
        QNetworkAccessManager *mgr;
        QNetworkReply *reply;
    protected slots:
        virtual void httpFinished() = 0;
        virtual void httpReadyRead() = 0;
    signals:
        void fetchedGamingMonth();
    public slots:
        void setDate(const QDate& copyDate)
        {
            _date = copyDate;
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
    private:
        QDate _date;

        int _typeProxy;
        QString _hostProxy;
        int _portProxy;
        QString _userProxy;
        QString _pwdProxy;

};

#endif // IDOWNLOADER_H
