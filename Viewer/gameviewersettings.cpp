#include <QSettings>

#include "gameviewersettings.h"
#include "constants.h"


GameViewerSettings::GameViewerSettings(QWidget *parent) : IViewSettings(parent)
{
    this->setWindowTitle(tr("Preferences"));
}

void GameViewerSettings::loadSavedSettings()
{
   qDebug();
   QSettings settings(appINI, QSettings::IniFormat);
   foreach(QString key, settings.allKeys())
   {
       qDebug()<<key;
       if (existedPropertyNames().contains(key))
       {
           setPropertyByString(key, settings.value(key, QVariant()));
       }
   }
   qDebug()<<"End"<<this->hostProxy();
   propertyChanged("HOST_PROXY");
   settings.setValue("HOST_PROXY", "TEST");
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
        qDebug()<<key;
        if ( existedPropertyNames().contains(key))
        {
            setPropertyByString(key, settings.value(key, QVariant()));
        }
    }
}
void GameViewerSettings::show()
{
    loadSavedSettings();
    clearChangedProperties();
    //TODO: отобразить настройки
    QWidget::show();
}
