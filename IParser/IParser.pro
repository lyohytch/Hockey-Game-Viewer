TARGET = parser
HEADERS += \
    iparser.h \
    parserkhlru.h \
    parsegamingmonth.h

SOURCES += \
    parserkhlru.cpp \
    parsegamingmonth.cpp

QT += xmlpatterns


LIBS += -L../build/bin -lioperation
include ( ../common.pri )
