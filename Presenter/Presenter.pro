TARGET = presenter

HEADERS += \
    iview.h \
    presentation.h \
    qthreadrunner.h \
    qthreadrunnerpool.h \
    IViewSettings.h

SOURCES += \
    presentation.cpp \
    qthreadrunner.cpp \
    qthreadrunnerpool.cpp

include ( ../presenter.pri )
