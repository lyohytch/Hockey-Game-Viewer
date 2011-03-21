#ifndef PARSERPOOL_H
#define PARSERPOOL_H

#include <QObject>
#include "iparser.h"

class ParserPool : public QObject
{
        Q_OBJECT
    public:
        explicit ParserPool(QObject* parent = 0);
        IParser* getParserByName(const QString& siteName);
        void appendParser(IParser* parser);

    signals:

    public slots:

    private:
        QList<IParser*> _parsers;

};

#endif // PARSERPOOL_H
