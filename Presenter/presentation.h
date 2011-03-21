#ifndef PRESENTATION_H
#define PRESENTATION_H

#include <QObject>
#include "iview.h"
#include "downloaderspool.h"
#include "parserpool.h"

class presentation: public QObject
{
    Q_OBJECT
public:
    explicit presentation(IView * _view);
signals:

private slots:
    void gamingDaySelected(const QDate & gameDay);
private:
    IView * view;
    DownloadersPool *downloaders;
    ParserPool *parsers;
    void createDownloadersList();
    void createParsersList();


};

#endif // PRESENTATION_H
