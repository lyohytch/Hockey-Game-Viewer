#ifndef GAMEVIEWER_H
#define GAMEVIEWER_H

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

    private:
        Ui::GameViewer* ui;
};

#endif // GAMEVIEWER_H
