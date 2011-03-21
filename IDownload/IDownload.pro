TARGET = downloader

HEADERS += \
    idownloader.h \
    downloaderspool.h \
    downloaderkhlru.h

SOURCES += \
    downloaderspool.cpp \
    downloaderkhlru.cpp

include ( ../common.pri )
