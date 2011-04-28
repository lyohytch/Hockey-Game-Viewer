#ifndef IVIEWSETTINGS_H
#define IVIEWSETTINGS_H

#include <QObject>
#include <QMap>
#include <QStringList>
#include <QVariant>

#include "constants_presenter.h"

class IViewSettings: public QObject
{
        Q_OBJECT
        //Proxy
        Q_PROPERTY(int typeProxy READ  typeProxy WRITE setTypeProxy)
        Q_PROPERTY(QString hostProxy READ hostProxy WRITE setHostProxy)
        Q_PROPERTY(int portProxy READ portProxy WRITE setPortProxy)
        Q_PROPERTY(QString userProxy READ userProxy WRITE setUserProxy)
        Q_PROPERTY(QString pwdProxy READ pwdProxy WRITE setPwdProxy)

    public:

        enum Properties
        {
            type_proxy = 0,
            host_proxy,
            port_proxy,
            user_proxy,
            pwd_proxy,
            unknown
        };

        IViewSettings(QObject* parent);

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

        QStringList existedPropertyNames() const
        {
            return _existedPropNames;
        }

        QStringList changedPropertyNames() const
        {
            return _changedPropNames;
        }

        void propertyChanged(const QString& propertyName);

        void clearChangedProperties();

        void setPropertyByString(const QString& prop, const QVariant& val);

        int stringToProperty(const QString& prop);

        QString propertyToString(Properties prop);

        void resetToDefaultSettings();

        void fillExistedPropertyNames();

        void prepareSettings();

        virtual void loadSavedSettings() = 0;
        virtual void checkChangedSettings() = 0;
        virtual void onePropertyChanged(const QString &, const QVariant &) = 0;

    signals:
        void ProxySettingsChanged();

    public slots:
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
        void setPwdProxy(const QString& pwd )
        {
            _pwdProxy = pwd;
        }

    private:
        int _typeProxy;
        QString _hostProxy;
        int _portProxy;
        QString _userProxy;
        QString _pwdProxy;
        QStringList _existedPropNames;
        QStringList _changedPropNames;
};

#endif // IVIEWSETTINGS_H
