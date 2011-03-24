TARGET = downloader

HEADERS += \
    idownloader.h \
    downloaderkhlru.h

SOURCES += \
    downloaderkhlru.cpp

LIBS += -L../build/bin -lioperation

include ( ../common.pri )
