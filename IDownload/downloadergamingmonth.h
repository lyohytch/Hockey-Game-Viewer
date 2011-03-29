#ifndef DOWNLOADERGAMINGMONTH_H
#define DOWNLOADERGAMINGMONTH_H

#include "downloaderkhlru.h"
class DownKhlRuGamingMonth : public DownloaderKhlRu
{
    Q_OBJECT
 public:
    DownKhlRuGamingMonth(QObject* parent = 0, const QString& siteName = "www.khl.ru") : DownloaderKhlRu(parent, siteName)
    {
        setInterval(20000);
    }
    virtual void run();
protected slots:
    virtual void httpFinished();
    virtual void httpReadyRead();
};

#endif // DOWNLOADERGAMINGMONTH_H
