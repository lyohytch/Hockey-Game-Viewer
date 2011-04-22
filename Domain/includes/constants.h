#ifndef CONSTANTS_H
#define CONSTANTS_H

#include <QDebug>
#include <QString>

#define qDebug()  qDebug()<<__FILE__<<":"<<__FUNCTION__<<"("<<__LINE__<<")"<<":"

const QString appINI("hgv.ini");

#endif  //CONSTANTS_H
