TARGET = khlru

LIBS += -L../../build/bin -loperations

D = Downloader
P = Parser
R = Reader

QT += xmlpatterns
QT += network

HEADERS += \
    $$D/d_onlinematches.h \
    $$D/d_common.h \
    $$D/d_pastmatches.h \
    $$R/r_onlinematches.h \
    $$R/r_common.h \
    $$R/r_pastmatches.h \
    $$P/p_onlinematches.h \
    $$P/p_common.h \
    $$P/p_pastmatches.h

SOURCES += \
    $$D/d_onlinematches.cpp \
    $$D/d_pastmatches.cpp \
    $$D/d_common.cpp \
    $$R/r_onlinematches.cpp \
    $$R/r_pastmatches.cpp \
    $$P/p_onlinematches.cpp \
    $$P/p_pastmatches.cpp \
    $$P/p_common.cpp

include( ../platforms.pri)
   
