TARGET = parser
HEADERS += \
    iparser.h \
    parserkhlru.h

SOURCES += \
    parserkhlru.cpp

LIBS += -L../build/bin -lioperation
include ( ../common.pri )
