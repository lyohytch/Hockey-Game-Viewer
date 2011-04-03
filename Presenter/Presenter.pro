TARGET = presenter

HEADERS += \
    iview.h \
    presentation.h \
    qthreadrunner.h \
    qthreadrunnerpool.h

SOURCES += \
    presentation.cpp \
    qthreadrunner.cpp \
    qthreadrunnerpool.cpp

include ( ../common.pri )
include ( ../presenter.pri )
