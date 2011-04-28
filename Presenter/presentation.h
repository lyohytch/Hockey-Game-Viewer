#ifndef PRESENTATION_H
#define PRESENTATION_H
#include <QStandardItemModel>

#include "iview.h"
#include "IViewSettings.h"
#include "operationpool.h"
#include "qthreadrunnerpool.h"

class presentation: public QObject
{
    Q_OBJECT
public:
    explicit presentation(IView * _view, IViewSettings *_viewSettings);
signals:

private slots:
    void gamingDaySelected(const QDate & gameDay);
    void downloadMonthResultsFinished(int error);
    void downloadDayResultsFinished(int error);
    void parsingMonthFinished();
    void parsingDayFinished();
    void EmptyReadingFile();
    void fillMatchesTable();
    void fillMatchesTodayTable();
    void proxySettingsChanged();
private:
    IView * view;
    IViewSettings *viewSettings;
    OperationPool *downloaders;
    OperationPool *parsers;
    OperationPool *readers;
    QThreadRunnerPool *runners;
    QStandardItemModel *tableModel;

    void createDownloadersList();
    void createReadersList();
    void createParsersList();
    void createRunnersList();
    void connectOnEvents();
};

#endif // PRESENTATION_H
