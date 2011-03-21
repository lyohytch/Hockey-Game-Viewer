#ifndef PARSERKHLRU_H
#define PARSERKHLRU_H

#include <QObject>
#include "iparser.h"
#include "constants.h"

class ParserKhlRu : public IParser
{
    Q_OBJECT
public:
    explicit ParserKhlRu(QObject *parent = 0, const QString &targetName = "www.khl.ru") : IParser(parent, targetName) {}
    virtual void run()
    {
        qDebug();
    }

signals:

public slots:

};

#endif // PARSERKHLRU_H
