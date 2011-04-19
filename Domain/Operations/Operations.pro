TARGET = operations

HEADERS += \
    ioperation.h \
    operationpool.h \
    ireader.h \
    idownloader.h \
    iparser.h

SOURCES += \
    operationpool.cpp

include ( ../../common.pri )
