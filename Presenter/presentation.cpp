#include "constants.h"

#include "presentation.h"
//Downloaders
#include "downloaderkhlru.h"

//Parsers
#include "parserkhlru.h"


presentation::presentation(IView* _view)
{
    view = _view;

    connect(view, SIGNAL(GamingDaySelected(const QDate&)), this,
            SLOT(gamingDaySelected(const QDate&)), Qt::AutoConnection);
    createDownloadersList();
    createParsersList();
}

void presentation::gamingDaySelected(const QDate& gameDay)
{
    qDebug()<<gameDay;

}

void presentation::createDownloadersList()
{
    downloaders = new DownloadersPool(this);
    downloaders->appendDownloader(new DownloaderKhlRu(downloaders));
}

void presentation::createParsersList()
{
   parsers = new ParserPool(this);
   parsers->appendParser(new ParserKhlRu(parsers));
}
