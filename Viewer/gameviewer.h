#ifndef GAMEVIEWER_H
#define GAMEVIEWER_H
#include <QLabel>
#include <QMainWindow>
#include <QTableView>
#include <QDateEdit>
#include <QPushButton>

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
    BasicViewer(QObject *parent = 0): IView(parent)
    {
        _table = new QTableView(0);
        _calendar = new QDateEdit(0);
        _stateLabel = new QLabel(0);
        _update = new QPushButton(0);
    }
    virtual ~BasicViewer()
    {
    }
    virtual void gamingDaySelected(const QDate & gameDate);
    virtual void setModel(QAbstractItemModel *model);
    virtual void resizeTable();
    QTableView *table() const
    {
        return _table;
    }
    QDateEdit *calendar()
    {
        return _calendar;
    }

    QLabel *stateLabel()
    {
        return _stateLabel;
    }

    QPushButton *update()
    {
        return _update;
    }

private:
    QTableView *_table;
    QDateEdit *_calendar;
    QLabel *_stateLabel;
    QPushButton *_update;
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

        GameViewerSettings *viewerSettingsForm;
        void init();

    private slots:
        void DateChanged(const QDate &date);
        void Update();
};


#endif // GAMEVIEWER_H
