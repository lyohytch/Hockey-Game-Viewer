TARGET = rwdata
HEADERS += \
    irwdata.h \
    rwkhlru.h \
    rwkhlrugamingday.h

SOURCES += \
    rwkhlru.cpp \
    rwkhlrugamingday.cpp

LIBS += -L../build/bin -lioperation

include ( ../common.pri )
