#include <QSettings>
#include <QVBoxLayout>
#include <QGridLayout>
#include <QTabWidget>

#include "gameviewersettings.h"
#include "constants.h"
#include "constants_presenter.h"


GameViewerSettings::GameViewerSettings(QWidget *parent) : IViewSettings(parent)
{
    //TODO: setup tab widget
    this->setWindowTitle(tr("Preferences"));
    //this->setGeometry(500, 500, 300, 300);
    //Creatings tabs
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

    //Connect
    connect(proxy_type, SIGNAL(currentIndexChanged(int)), this, SLOT(typeProxyChanged(int)));
    connect(proxy_host, SIGNAL(textChanged(QString)), this, SLOT(hostProxyChanged(QString)));
    connect(proxy_port, SIGNAL(valueChanged(int)), this, SLOT(portProxyChanged(int)));
    connect(proxy_user, SIGNAL(textChanged(QString)), this, SLOT(userProxyChanged(QString)));
    connect(proxy_pwd, SIGNAL(textChanged(QString)), this, SLOT(pwdProxyChanged(QString)));

    //

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
    QWidget *TBD = new QWidget;
    //Creating tabWidget
    tabs = new QTabWidget;
    //Adding tabs
    tabs->addTab(proxy, tr("Setup proxy"));

    //tabs->setTabShape(QTabWidget::Triangular);


    tabs->addTab(TBD, "TBD");
    layout = new QVBoxLayout(this);
    layout->addWidget(tabs);
    this->setLayout(layout);

}

void GameViewerSettings::typeProxyChanged(int copyType)
{
    qDebug();
    QSettings settings(appINI, QSettings::IniFormat);
    settings.setValue(TYPE_PROXY, copyType);
    propertyChanged(TYPE_PROXY);
}

void GameViewerSettings::hostProxyChanged(QString copyhost)
{
    qDebug();
    QSettings settings(appINI, QSettings::IniFormat);
    settings.setValue(HOST_PROXY, copyhost);
    propertyChanged(HOST_PROXY);
}

void GameViewerSettings::portProxyChanged(int copyport)
{
    qDebug();
    QSettings settings(appINI, QSettings::IniFormat);
    settings.setValue(PORT_PROXY, copyport);
    propertyChanged(PORT_PROXY);
}

void GameViewerSettings::userProxyChanged(QString copyuser)
{
    qDebug();
    QSettings settings(appINI, QSettings::IniFormat);
    settings.setValue(USER_PROXY, copyuser);
    propertyChanged(USER_PROXY);
}

void GameViewerSettings::pwdProxyChanged(QString copypwd)
{
    qDebug();
    QSettings settings(appINI, QSettings::IniFormat);
    settings.setValue(PWD_PROXY, copypwd);
    propertyChanged(PWD_PROXY);
}

void GameViewerSettings::loadSavedSettings()
{
   qDebug();
   QSettings settings(appINI, QSettings::IniFormat);
   foreach(QString key, settings.allKeys())
   {
       qDebug()<<"KEY"<<":"<<key;
       if (existedPropertyNames().contains(key))
       {
           qDebug()<<"VALUE"<<":"<<settings.value(key, QVariant());
           setPropertyByString(key, settings.value(key, QVariant()));
       }
   }

   proxy_type->setCurrentIndex(typeProxy());
   proxy_host->setText(hostProxy());
   proxy_port->setValue(portProxy());
   proxy_user->setText(userProxy());
   proxy_pwd->setText(pwdProxy());

}

void GameViewerSettings::saveSettings()
{
    qDebug();
}

void GameViewerSettings::closeEvent(QCloseEvent *)
{
    // Настройки применяются после закрытия окна
    qDebug();
    QSettings settings(appINI, QSettings::IniFormat);
    foreach(QString key, changedPropertyNames())
    {
        qDebug()<<"Changed key"<<":"<<key;
        if ( existedPropertyNames().contains(key))
        {
            setPropertyByString(key, settings.value(key, QVariant()));
        }
    }
    if ( changedPropertyNames().count() > 0)
    {
        emit ProxySettingsChanged();
    }
}
void GameViewerSettings::show()
{
    loadSavedSettings();
    clearChangedProperties();
    //TODO: отобразить настройки
    QWidget::show();
}
