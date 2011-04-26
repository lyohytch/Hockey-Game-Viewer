INCLUDEPATH += . \
               .. \
               ../Domain/includes \
               ../Domain/Operations \
               ../Platforms/KhlRu/Downloader \
               ../Platforms/KhlRu/Parser \
               ../Platforms/KhlRu/Reader

OTHER_FILES += ../Domain/includes/constants.h \
               ../Domain/includes/constants_downloader.h \
               ../Domain/includes/constants_presenter.h

TEMPLATE = lib

QT += network core

unix:DESTDIR = ../build/bin
win32:DESTDIR = ../build/lib/$$TARGET
win32:DLLDESTDIR = ../build/bin
MOC_DIR = ../build/mocs/$$TARGET
OBJECTS_DIR = ../build/objs/$$TARGET

## CONFIG settings(debug)
CONFIG += debug
CONFIG -= release
DEFINES += DEBUGING
DEFINES += PROS

## CONFIG settings (release)
#CONFIG += release
#CONFIG -= debug
#DEFINES += QT_NO_DEBUG QT_NO_DEBUG_OUTPUT QT_NO_WARNING_OUTPUT

LIBS += -L../build/bin -lparser -ldownloader -loperations -lreader
