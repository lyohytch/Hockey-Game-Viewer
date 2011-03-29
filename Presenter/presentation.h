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
private:
    IView * view;
    OperationPool *downloaders;
    OperationPool *parsers;
    QThreadRunnerPool *runners;

    void createDownloadersList();
    void createParsersList();
    void createRunnersList();
    void connectOnEvents();
};

#endif // PRESENTATION_H
