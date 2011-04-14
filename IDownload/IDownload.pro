TARGET = downloader

HEADERS += \
    idownloader.h \
    downloaderkhlru.h \
    downloadergamingmonth.h \
    downloaderkhlrugamingday.h

SOURCES += \
    downloaderkhlru.cpp \
    downloadergamingmonth.cpp \
    downloaderkhlrugamingday.cpp

LIBS += -L../build/bin -lioperation

QT += network

include ( ../common.pri )
