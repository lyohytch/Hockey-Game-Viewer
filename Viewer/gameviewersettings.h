#ifndef GAMEVIEWERSETTINGS_H
#define GAMEVIEWERSETTINGS_H
#include <QComboBox>
#include <QTabWidget>
#include <QLineEdit>
#include <QSpinBox>
#include <QLayout>
#include <QLabel>

#include "IViewSettings.h"

class BasicViewerSettings: public IViewSettings
{
    Q_OBJECT
public:
    BasicViewerSettings(QObject *parent = 0): IViewSettings(parent) {}
    virtual ~BasicViewerSettings(){}
    virtual void loadSavedSettings();
    virtual void checkChangedSettings();
    virtual void onePropertyChanged(const QString &prop, const QVariant & value);
};

class GameViewerSettings: public QWidget
{
    Q_OBJECT
public:
    GameViewerSettings(QWidget *parent = 0);
    ~GameViewerSettings() {}
    void closeEvent(QCloseEvent *);
    BasicViewerSettings * getBasicViewerSettings()
    {
        return viewerSettings;
    }

public slots:
        void show();
    private:
        BasicViewerSettings *viewerSettings;
        //Screens
        QWidget *proxy;
        QWidget *TBD;

        //Proxy-Screen
        QGridLayout *proxy_layout;
        //Labels
        QLabel * proxy_type_txt;
        QLabel * proxy_host_txt;
        QLabel * proxy_port_txt;
        QLabel * proxy_user_txt;
        QLabel * proxy_pwd_txt;
        //Editors
        QComboBox * proxy_type;
        QLineEdit *proxy_host;
        QSpinBox *proxy_port;
        QLineEdit *proxy_user;
        QLineEdit *proxy_pwd;

        //Main
        QTabWidget *tabs;
        QLayout *layout;

        void setupMainWidget();
        void setValuesForElements();
         //Create Screens
        void createProxyScreen();
        void createTBDScreen();

        //Additional setup for screens
        void ProxyScreenCreateElements();
        void ProxyScreenRegisteringEventsFromElements();
        void ProxyScreenSetupLayout();
    private slots:
        void typeProxyChanged(int);
        void hostProxyChanged(QString);
        void portProxyChanged(int);
        void userProxyChanged(QString);
        void pwdProxyChanged(QString);
};

#endif // GAMEVIEWERSETTINGS_H
