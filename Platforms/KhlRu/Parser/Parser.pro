TARGET = parser
HEADERS += \
    onlinematches.h \
    common.h \
    pastmatches.h

SOURCES += \
    onlinematches.cpp \
    pastmatches.cpp

QT += xmlpatterns


LIBS += -L../../../build/bin -loperations
include ( ../../platforms.pri )
