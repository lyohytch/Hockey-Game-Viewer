#ifndef DOWNLOADERGAMINGMONTH_H
#define DOWNLOADERGAMINGMONTH_H

#include "downloaderkhlru.h"
class ReceiverKhlRuGamingMonth : public IReceiver
{
    Q_OBJECT
    ReceiverKhlRuGamingMonth(QObject *parent = 0, const QString &fname = 0): IReceiver(parent, fname)
    {
        file = new QFile(fname);
        file->open(QIODevice::WriteOnly);
    }
protected slots:
 virtual void httpFinished();
 virtual void httpReadyRead();
};

class DownKhlRuGamingMonth : public DownloaderKhlRu
{
    Q_OBJECT
 public:
    DownKhlRuGamingMonth(QObject* parent = 0, const QString& siteName = "www.khl.ru") : DownloaderKhlRu(parent, siteName)
    {
        setInterval(20000);
    }
    virtual void run();
};

#endif // DOWNLOADERGAMINGMONTH_H
