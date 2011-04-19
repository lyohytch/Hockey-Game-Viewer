TARGET = reader
HEADERS += \
    onlinematches.h \
    common.h \
    pastmatches.h

SOURCES +=  \
    onlinematches.cpp \
    pastmatches.cpp

LIBS += -L../../../build/bin -loperations

include ( ../../platforms.pri )
