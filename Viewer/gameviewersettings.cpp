#include <QSettings>
#include <QVBoxLayout>
#include <QGridLayout>
#include <QTabWidget>

#include "gameviewersettings.h"
#include "constants.h"
#include "constants_presenter.h"

void BasicViewerSettings::loadSavedSettings()
{
    qDebug();
    QSettings settings(appINI, QSettings::IniFormat);
    foreach(QString key, settings.allKeys())
    {
        qDebug() << "KEY" << ":" << key;
        if (existedPropertyNames().contains(key))
        {
            qDebug() << "VALUE" << ":" << settings.value(key, QVariant());
            setPropertyByString(key, settings.value(key, QVariant()));
        }
    }
}

void BasicViewerSettings::checkChangedSettings()
{
    // Настройки применяются после закрытия окна
    qDebug();
    QSettings settings(appINI, QSettings::IniFormat);
    foreach(QString key, changedPropertyNames())
    {
        qDebug() << "Changed key" << ":" << key;
        if (existedPropertyNames().contains(key))
        {
            setPropertyByString(key, settings.value(key, QVariant()));
        }
    }
    if (changedPropertyNames().count() > 0)
    {
        emit ProxySettingsChanged();
    }
}

void BasicViewerSettings::onePropertyChanged(const QString& prop, const QVariant& value)
{
    qDebug();
    QSettings settings(appINI, QSettings::IniFormat);
    settings.setValue(prop, value);
    propertyChanged(prop);
}


GameViewerSettings::GameViewerSettings(QWidget* parent) : QWidget(parent)
{
    createProxyScreen();
    createTBDScreen();

    setupMainWidget();

    viewerSettings = new BasicViewerSettings(this);

}

void GameViewerSettings::createTBDScreen()
{
    TBD = new QWidget;
}

void GameViewerSettings::setupMainWidget()
{
    setWindowTitle(tr("Preferences"));

    tabs = new QTabWidget;
    tabs->addTab(proxy, tr("Setup proxy"));
    tabs->addTab(TBD, "TBD");

    layout = new QVBoxLayout(this);
    layout->addWidget(tabs);
    setLayout(layout);
}

void GameViewerSettings::createProxyScreen()
{
    ProxyScreenCreateElements();
    ProxyScreenRegisteringEventsFromElements();
    ProxyScreenSetupLayout();
}

void GameViewerSettings::ProxyScreenCreateElements()
{
    proxy = new QWidget;
    proxy_layout = new QGridLayout(proxy);
    proxy_layout->setSizeConstraint(QGridLayout::SetMinimumSize);
    //Labels
    proxy_type_txt = new QLabel(tr("Type"));
    proxy_host_txt = new QLabel(tr("Host"));
    proxy_port_txt = new QLabel(tr("Port"));
    proxy_user_txt = new QLabel(tr("User"));
    proxy_pwd_txt = new QLabel(tr("Password"));
    //Editors
    proxy_type = new QComboBox;
    proxy_type->addItem(tr("Default system proxy"), Qt::UserRole + 1);
    proxy_type->addItem(tr("Socks proxy"), Qt::UserRole + 1);
    proxy_type->addItem(tr("No proxy"), Qt::UserRole + 1);
    proxy_type->addItem(tr("HTTP proxy"), Qt::UserRole + 1);
    proxy_type->addItem(tr("Secure HTTP proxy"), Qt::UserRole + 1);
    proxy_type->addItem(tr("FTP proxy"), Qt::UserRole + 1);

    proxy_host = new QLineEdit;
    proxy_port = new QSpinBox;
    proxy_port->setMaximum(99999);
    proxy_port->setMinimum(0);
    proxy_user = new QLineEdit;
    proxy_pwd = new QLineEdit;
}

void GameViewerSettings::ProxyScreenRegisteringEventsFromElements()
{
    connect(proxy_type, SIGNAL(currentIndexChanged(int)), this, SLOT(typeProxyChanged(int)));
    connect(proxy_host, SIGNAL(textChanged(QString)), this, SLOT(hostProxyChanged(QString)));
    connect(proxy_port, SIGNAL(valueChanged(int)), this, SLOT(portProxyChanged(int)));
    connect(proxy_user, SIGNAL(textChanged(QString)), this, SLOT(userProxyChanged(QString)));
    connect(proxy_pwd, SIGNAL(textChanged(QString)), this, SLOT(pwdProxyChanged(QString)));
}

void GameViewerSettings::ProxyScreenSetupLayout()
{
    proxy_layout->addWidget(proxy_type_txt, 0, 0);
    proxy_layout->addWidget(proxy_host_txt, 1, 0);
    proxy_layout->addWidget(proxy_port_txt, 2, 0);
    proxy_layout->addWidget(proxy_user_txt, 3, 0);
    proxy_layout->addWidget(proxy_pwd_txt, 4, 0);
    proxy_layout->addWidget(proxy_type, 0, 1);
    proxy_layout->addWidget(proxy_host, 1, 1);
    proxy_layout->addWidget(proxy_port, 2, 1);
    proxy_layout->addWidget(proxy_user, 3, 1);
    proxy_layout->addWidget(proxy_pwd, 4, 1);

    proxy->setLayout(proxy_layout);
}

void GameViewerSettings::typeProxyChanged(int copyType)
{
    viewerSettings->onePropertyChanged(TYPE_PROXY, copyType);
}

void GameViewerSettings::hostProxyChanged(QString copyhost)
{
    viewerSettings->onePropertyChanged(HOST_PROXY, copyhost);
}

void GameViewerSettings::portProxyChanged(int copyport)
{
    viewerSettings->onePropertyChanged(PORT_PROXY, copyport);
}

void GameViewerSettings::userProxyChanged(QString copyuser)
{
    viewerSettings->onePropertyChanged(USER_PROXY, copyuser);
}

void GameViewerSettings::pwdProxyChanged(QString copypwd)
{
    viewerSettings->onePropertyChanged(PWD_PROXY, copypwd);
}

void GameViewerSettings::closeEvent(QCloseEvent*)
{
    viewerSettings->checkChangedSettings();
}
void GameViewerSettings::show()
{
    viewerSettings->loadSavedSettings();
    setValuesForElements();
    viewerSettings->clearChangedProperties();

    QWidget::show();
}

void GameViewerSettings::setValuesForElements()
{
    proxy_type->setCurrentIndex(viewerSettings->typeProxy());
    proxy_host->setText(viewerSettings->hostProxy());
    proxy_port->setValue(viewerSettings->portProxy());
    proxy_user->setText(viewerSettings->userProxy());
    proxy_pwd->setText(viewerSettings->pwdProxy());
}
