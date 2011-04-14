TARGET = parser
HEADERS += \
    iparser.h \
    parserkhlru.h \
    parsegamingmonth.h \
    parserkhlrugamingday.h

SOURCES += \
    parserkhlru.cpp \
    parsegamingmonth.cpp \
    parserkhlrugamingday.cpp

QT += xmlpatterns


LIBS += -L../build/bin -lioperation
include ( ../common.pri )
