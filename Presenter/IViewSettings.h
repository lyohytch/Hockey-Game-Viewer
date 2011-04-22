#ifndef IVIEWSETTINGS_H
#define IVIEWSETTINGS_H

#include <QWidget>
#include <QMap>
#include <QString>
#include <QVariant>

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
            TYPE_PROXY,
            HOST_PROXY,
            PORT_PROXY,
            USER_PROXY,
            PWD_PROXY,
            UNKNOWN
        };
        IViewSettings(QWidget* parent = 0) : QWidget(parent)
        {        }

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

        void propertyChanged(const QString &propertyName)
        {
            _changedPropNames.append(propertyName);
        }

        void clearChangedProperties()
        {
            _changedPropNames.clear();
        }

        QString propertyToString(Properties prop)
        {
            switch (prop)
            {
                case TYPE_PROXY:
                    return "TYPE_PROXY";
                case HOST_PROXY:
                    return "HOST_PROXY";
                case PORT_PROXY:
                    return "PORT_PROXY";
                case USER_PROXY:
                    return "USER_PROXY";
                case PWD_PROXY:
                    return "PWD_PROXY";
                default:
                    return "UNKNOWN";
            }
        }

        void setPropertyByString(const QString& prop, const QVariant & val)
        {
            if (prop == "TYPE_PROXY")
            {
                if (!val.isNull() && val.type() == QVariant::Int)
                {
                    setTypeProxy(val.toInt());
                }
            }

            else if (prop == "HOST_PROXY")
            {
                if (!val.isNull() && val.type() == QVariant::String)
                {
                    setHostProxy(val.toString());
                }
            }

            else if (prop == "PORT_PROXY")
            {
                if (!val.isNull() && val.type() == QVariant::Int)
                {
                    setPortProxy(val.toInt());
                }
            }
            else if (prop == "USER_PROXY")
            {
                if (!val.isNull() && val.type() == QVariant::String)
                {
                    setUserProxy(val.toString());
                }
            }
            else if (prop == "PWD_PROXY") {
                if (!val.isNull() && val.type() == QVariant::String)
                {
                    setPwdProxy(val.toString());
                }
            }
        }

        int StringToProperty(const QString& prop)
        {
            if (prop == "TYPE_PROXY") return TYPE_PROXY;
            else if (prop == "HOST_PROXY") return HOST_PROXY;
            else if (prop == "PORT_PROXY") return PORT_PROXY;
            else if (prop == "USER_PROXY") return USER_PROXY;
            else if (prop == "PWD_PROXY") return PWD_PROXY;
            else return UNKNOWN;
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
            for (int i = 0; i < UNKNOWN; ++i)
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
