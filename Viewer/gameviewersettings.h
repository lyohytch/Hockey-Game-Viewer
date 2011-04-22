#ifndef GAMEVIEWERSETTINGS_H
#define GAMEVIEWERSETTINGS_H

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
};

#endif // GAMEVIEWERSETTINGS_H
