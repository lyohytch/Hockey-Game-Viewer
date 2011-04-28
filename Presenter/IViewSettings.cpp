#include "IViewSettings.h"

IViewSettings::IViewSettings(QObject *parent = 0): QObject(parent)
{
    _typeProxy = 0;
    _hostProxy = QString();
    _portProxy = 0;
    _userProxy = QString();
    _pwdProxy = QString();
}

void IViewSettings::propertyChanged(const QString &propertyName)
{
    if (!_changedPropNames.contains(propertyName))
    {
        _changedPropNames.append(propertyName);
    }
}

void IViewSettings::clearChangedProperties()
{
    _changedPropNames.clear();
}

void IViewSettings::setPropertyByString(const QString &prop, const QVariant &val)
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

int IViewSettings::stringToProperty(const QString &prop)
{
    if (prop == TYPE_PROXY) return type_proxy;
    else if (prop == HOST_PROXY) return host_proxy;
    else if (prop == PORT_PROXY) return port_proxy;
    else if (prop == USER_PROXY) return user_proxy;
    else if (prop == PWD_PROXY) return pwd_proxy;
    else return unknown;
}

QString IViewSettings::propertyToString(Properties prop)
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

void IViewSettings::resetToDefaultSettings()
{
    setTypeProxy(0);
    setHostProxy(QString());
    setPortProxy(0);
    setUserProxy(QString());
    setPwdProxy(QString());
}

void IViewSettings::fillExistedPropertyNames()
{
    for (int i = 0; i < unknown; ++i)
    {
        _existedPropNames.append(propertyToString((Properties)i));
    }
}

void IViewSettings::prepareSettings()
{
    fillExistedPropertyNames();
    loadSavedSettings();
}
