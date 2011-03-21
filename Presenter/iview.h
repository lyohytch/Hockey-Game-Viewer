#ifndef IVIEW_H
#define IVIEW_H

#include <QMainWindow>
#include <QDate>

class IView : public QMainWindow
{
    Q_OBJECT
    Q_PROPERTY(QString downloaderName READ downloaderName WRITE setdownloaderName)
public:
    explicit IView(QWidget *parent = 0) : QMainWindow(parent) {}
    QString downloaderName() const
    {
        return _downloaderName;
    }

signals:
    void GamingDaySelected(const QDate &gameDate);
public slots:
    void setdownloaderName(const QString & copySite)
    {
        _downloaderName = copySite;
    }

private:
   QString _downloaderName;
};

#endif // IVIEW_H
