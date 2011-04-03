TARGET = downloader

HEADERS += \
    idownloader.h \
    downloaderkhlru.h \
    downloadergamingmonth.h

SOURCES += \
    downloaderkhlru.cpp \
    downloadergamingmonth.cpp

LIBS += -L../build/bin -lioperation

QT += network

include ( ../common.pri )
