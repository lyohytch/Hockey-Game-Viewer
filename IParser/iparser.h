#ifndef IPARSER_H
#define IPARSER_H

#include <QObject>
#include <QRunnable>

class IParser : public QObject, public QRunnable
{
        Q_OBJECT
        Q_PROPERTY(QString targetSite READ targetSite)
    public:
        explicit IParser(QObject* parent = 0 , const QString& siteName = 0) : QObject(parent), _targetSite(siteName) {}
        QString targetSite() const
        {
            return _targetSite;
        }
    signals:

    public slots:

    private:
        QString _targetSite;
};

#endif // IPARSER_H
