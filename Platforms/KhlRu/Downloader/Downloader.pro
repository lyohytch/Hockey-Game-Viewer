TARGET = downloader

HEADERS += \
    onlinematches.h \
    common.h \
    pastmatches.h

SOURCES += \
    onlinematches.cpp \
    pastmatches.cpp \
    common.cpp

LIBS += -L../../../build/bin -loperations

QT += network

include ( ../../platforms.pri )
