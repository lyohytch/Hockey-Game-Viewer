#include <QtGui/QApplication>
#include <QtNetwork/QNetworkProxy>
#include "gameviewer.h"

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    GameViewer w;
    w.show();

    return a.exec();
}
