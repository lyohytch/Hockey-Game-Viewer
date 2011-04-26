#ifndef GAMEVIEWERSETTINGS_H
#define GAMEVIEWERSETTINGS_H
#include <QComboBox>
#include <QTabWidget>
#include <QLineEdit>
#include <QSpinBox>
#include <QLayout>
#include <QLabel>

#include "IViewSettings.h"
class GameViewerSettings: public IViewSettings
{
    Q_OBJECT
public:
    GameViewerSettings(QWidget *parent = 0);
    ~GameViewerSettings() {}
    virtual void loadSavedSettings();
    virtual void saveSettings();
    void closeEvent(QCloseEvent *);
public slots:
        void show();
    private:
        QWidget *proxy;
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

        QTabWidget *tabs;
        QLayout *layout;
    private slots:
        void typeProxyChanged(int);
        void hostProxyChanged(QString);
        void portProxyChanged(int);
        void userProxyChanged(QString);
        void pwdProxyChanged(QString);
};

#endif // GAMEVIEWERSETTINGS_H
