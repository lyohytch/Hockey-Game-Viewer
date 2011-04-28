#ifndef GAMEVIEWER_H
#define GAMEVIEWER_H
#include <QLabel>
#include <QMainWindow>

#include "iview.h"
#include "presentation.h"
#include "gameviewersettings.h"

namespace Ui
{
    class GameViewer;
}

class BasicViewer: public IView
{
    Q_OBJECT
public:
    BasicViewer(QObject *parent = 0): IView(parent){}
    virtual ~BasicViewer() {}
    virtual void gamingDaySelected(const QDate & gameDate);
};

class GameViewer : public QMainWindow
{
        Q_OBJECT

    public:
        explicit GameViewer(QWidget* parent = 0);
        virtual  ~GameViewer();
        BasicViewer * getViewer()
        {
            return view;
        }

    protected slots:
        virtual void setStatusOnForm(const QString& status);

    private:
        BasicViewer *view;
        BasicViewerSettings *viewerSettings;
        Ui::GameViewer* ui;
        QLabel *stateLabel;
        GameViewerSettings *viewerSettingsForm;
        void init();

    private slots:
        void DateChanged(const QDate &date);
};


#endif // GAMEVIEWER_H
