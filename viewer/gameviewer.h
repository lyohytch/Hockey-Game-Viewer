#ifndef GAMEVIEWER_H
#define GAMEVIEWER_H
#include <QLabel>
#include "iview.h"
#include "presentation.h"

namespace Ui
{
    class GameViewer;
}

class GameViewer : public IView
{
        Q_OBJECT

    public:
        explicit GameViewer(QWidget* parent = 0);
        ~GameViewer();
    protected slots:
        virtual void setStatusOnForm(const QString& status);

    private:
        Ui::GameViewer* ui;
        QLabel *stateLabel;
        void init();

    private slots:
        void DateChanged(const QDate &date);
};


#endif // GAMEVIEWER_H
