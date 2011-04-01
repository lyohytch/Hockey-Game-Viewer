#ifndef PRESENTATION_H
#define PRESENTATION_H
#include <QObject>
#include <QtNetwork/QNetworkProxy>
#include <QtNetwork/QNetworkAccessManager>
#include <QtNetwork/QNetworkReply>
#include <QtNetwork/QNetworkRequest>
#include <QUrl>
#include <QFile>

#include "iview.h"
#include "operationpool.h"
#include "qthreadrunnerpool.h"

class presentation: public QObject
{
    Q_OBJECT
public:
    explicit presentation(IView * _view);
signals:

private slots:
    void gamingDaySelected(const QDate & gameDay);
    void downloadFinished();
    void parsingFinished();
    void EmptyReadingFile();
private:
    IView * view;
    OperationPool *downloaders;
    OperationPool *parsers;
    OperationPool *readers;
    QThreadRunnerPool *runners;

    QDate selectedDay;

    void createDownloadersList();
    void createReadersList();
    void createParsersList();
    void createRunnersList();
    void connectOnEvents();
};

#endif // PRESENTATION_H
