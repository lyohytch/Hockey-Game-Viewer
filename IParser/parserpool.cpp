#include "parserpool.h"

ParserPool::ParserPool(QObject* parent) :
    QObject(parent)
{
}

IParser* ParserPool::getParserByName(const QString& siteName)
{
    foreach(IParser * ps, _parsers)
    {
        if (ps->targetSite() == siteName)
        {
            return ps;
        }
    }
    return 0;
}

void ParserPool::appendParser(IParser* parser)
{
    _parsers.append(parser);
}
