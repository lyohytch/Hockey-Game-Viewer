#ifndef CONSTANTS_DOWNLOADER_H
#define CONSTANTS_DOWNLOADER_H
#include <QString>
#include <QMap>

const QString ResTmpDownloadPath("Resources/tmp/dwn/");
const QString ResTmpParsePath("Resources/tmp/parse/");
const QString KhlRuName("www.khl.ru/");
const QString KhlRuUrl("http://www.khl.ru/");


//To config for www.khl.ru
const QString GameMonth("calendar/");

const QString Regular_1("160"); //Season 2008-2009
const QString PlayOffs_1("165");
const QString Regular_2("167");//Season 2009-2010
const QString PlayOffs_2("168");
const QString Regular_3("185");//Season 2010-2011
const QString PlayOffs_3("186");


//Process in other file
struct Season
{
    Season(int y_start, int m_start, int y_end, int m_end, int y_po, int m_po)
    {
        yearStart = y_start;
        monthStart = m_start;
        yearEnd = y_end;
        monthEnd = m_end;
        yearPlayOff = y_po;
        monthPlayOff = m_po;
    }

    int yearStart;
    int monthStart;
    int yearEnd;
    int monthEnd;
    int yearPlayOff;
    int monthPlayOff;
};
struct MapValue
{
    MapValue(int _y, const QString &_aUrl)
    {
        year = _y;
        addUrl = _aUrl;
    }

    int year;
    QString addUrl;
};

const QList<MapValue> regulars (QList<MapValue>()<<MapValue(2008, Regular_1) <<
                                                   MapValue(2009, Regular_2) <<
                                                   MapValue(2010, Regular_3));
const QList<MapValue> playoffs (QList<MapValue>()<<MapValue(2009, PlayOffs_1) <<
                                                   MapValue(2010, PlayOffs_2) <<
                                                   MapValue(2011, PlayOffs_3));


const QList<Season> seasons(QList<Season>() << Season(2008, 9, 2009, 5, 2009, 3) <<
                            Season(2009, 9, 2010, 5, 2010, 3) <<
                            Season(2010, 9, 2011, 5, 2011, 3));

#define isRegular(date, season)   ((date.year()==season.yearStart && date.month() >= season.monthStart) || \
        (date.year()==season.yearPlayOff && date.month() < season.monthPlayOff))
#define isPlayOffs(date, season)  (date.year() == season.yearPlayOff && date.month() >= season.monthPlayOff &&  \
        (date.year() == season.yearEnd && date.month() < season.monthEnd))

#endif // CONSTANTS_DOWNLOADER_H
