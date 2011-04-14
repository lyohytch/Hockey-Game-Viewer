TARGET = rwdata
HEADERS += \
    irwdata.h \
    rwkhlru.h \
    rwkhlrugamingday.h \
    rwkhlrugamingday_tmp.h

SOURCES += \
    rwkhlru.cpp \
    rwkhlrugamingday.cpp \
    rwkhlrugamingday_tmp.cpp

LIBS += -L../build/bin -lioperation

include ( ../common.pri )
