#ifndef IVIEWSETTINGS_H
#define IVIEWSETTINGS_H

#include <QWidget>
#include <QMap>
#include <QString>
#include <QVariant>

#include "constants_presenter.h"

class IViewSettings: public QWidget
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

        IViewSettings(QWidget* parent = 0) : QWidget(parent)
        {
            _typeProxy = 0;
            _hostProxy = QString();
            _portProxy = 0;
            _userProxy = QString();
            _pwdProxy = QString();
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

        QStringList existedPropertyNames() const
        {
            return _existedPropNames;
        }

        QStringList changedPropertyNames() const
        {
            return _changedPropNames;
        }

        void propertyChanged(const QString& propertyName)
        {
            if (!_changedPropNames.contains(propertyName))
            {
                _changedPropNames.append(propertyName);
            }
        }

        void clearChangedProperties()
        {
            _changedPropNames.clear();
        }

        void setPropertyByString(const QString& prop, const QVariant& val)
        {
            if (!val.isNull())
            {
                if (prop == TYPE_PROXY)
                {
                    setTypeProxy(val.toInt());
                }

                else if (prop == HOST_PROXY)
                {
                    setHostProxy(val.toString());
                }

                else if (prop == PORT_PROXY)
                {
                    setPortProxy(val.toInt());
                }
                else if (prop == USER_PROXY)
                {
                    setUserProxy(val.toString());
                }
                else if (prop == PWD_PROXY)
                {
                    setPwdProxy(val.toString());
                }
            }
        }

        int stringToProperty(const QString& prop)
        {
            if (prop == TYPE_PROXY) return type_proxy;
            else if (prop == HOST_PROXY) return host_proxy;
            else if (prop == PORT_PROXY) return port_proxy;
            else if (prop == USER_PROXY) return user_proxy;
            else if (prop == PWD_PROXY) return pwd_proxy;
            else return unknown;
        }

        QString propertyToString(Properties prop)
        {
            switch (prop)
            {
                case type_proxy:
                    return TYPE_PROXY;
                case host_proxy:
                    return HOST_PROXY;
                case port_proxy:
                    return PORT_PROXY;
                case user_proxy:
                    return USER_PROXY;
                case pwd_proxy:
                    return PWD_PROXY;
                default:
                    return UNKNOWN;
            }
        }

        void resetToDefaultSettings()
        {
            setTypeProxy();
            setHostProxy();
            setPortProxy();
            setUserProxy();
            setPwdProxy();
        }

        void fillExistedPropertyNames()
        {
            for (int i = 0; i < unknown; ++i)
            {
                _existedPropNames.append(propertyToString((Properties)i));
            }
        }

        void prepareSettings()
        {
            fillExistedPropertyNames();
            loadSavedSettings();
        }

        virtual void loadSavedSettings() = 0;
        virtual void saveSettings() = 0;

    signals:
        void ProxySettingsChanged();

    public slots:
        void setTypeProxy(int type = 0)
        {
            _typeProxy = type;
        }
        void setHostProxy(const QString& host = "")
        {
            _hostProxy = host;
        }
        void setPortProxy(int port = 0)
        {
            _portProxy = port;
        }
        void setUserProxy(const QString& user = "")
        {
            _userProxy = user;
        }
        void setPwdProxy(const QString& pwd = "")
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
