#ifndef IDOWNLOADER_H
#define IDOWNLOADER_H

#include <QDate>
#include <QFile>
#include <QtNetwork/QNetworkProxy>
#include <QtNetwork/QNetworkAccessManager>
#include <QtNetwork/QNetworkReply>
#include <QtNetwork/QNetworkRequest>

#include "ioperation.h"
#include "constants_downloader.h"

class IReceiver: public QObject
{
        Q_OBJECT
    public:
        IReceiver(QNetworkAccessManager* _mgr, QFile* _file):
            mgr(_mgr), file(_file) {}
    signals:
        void finished();
    public slots:
        virtual void httpFinished() = 0;
        virtual void httpReadyRead() = 0;
    protected:
        QNetworkAccessManager* mgr;
        QNetworkReply* reply;
        QFile* file;
};

class IDownloader : public IOperation
{
        Q_OBJECT

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
        virtual void setupUrlAndFileByDate() = 0;
        virtual void launchDownloadingProcess() = 0;
        QString urlForDownload;
        QString fileForSave;
    signals:
        void fetchedGamingMonth();
    public slots:
        void setTypeProxy(int type)
        {
            _typeProxy = type;
        }
        void setHostProxy(QString host)
        {
            _hostProxy = host;
        }
        void setPortProxy(int port)
        {
            _portProxy = port;
        }
        void setUserProxy(QString user)
        {
            _userProxy = user;
        }
        void setPwdProxy(QString pwd)
        {
            _pwdProxy = pwd;
        }
    private:

        int _typeProxy;
        QString _hostProxy;
        int _portProxy;
        QString _userProxy;
        QString _pwdProxy;

};

#endif // IDOWNLOADER_H
