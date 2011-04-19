#ifndef RWKHLRU_H
#define RWKHLRU_H

#include <QObject>
#include <QDateTime>
#include <QThread>

#include "ireader.h"

class RWKhlRu:public IRWData
{
public:
    RWKhlRu(QObject *parent = 0, const QString &targetSite = "www.khl.ru"): IRWData(parent, targetSite) {}
};

#endif // RWKHLRU_H
