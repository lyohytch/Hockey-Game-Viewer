TARGET = parser
HEADERS += \
    iparser.h \
    parserpool.h \
    parserkhlru.h

SOURCES += \
    parserpool.cpp \
    parserkhlru.cpp

include ( ../common.pri )
