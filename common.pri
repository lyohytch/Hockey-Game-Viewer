INCLUDEPATH += . .. ../includes ../IOperation
OTHER_FILES += ../includes/constants.h \
               ../includes/constants_downloader.h
TEMPLATE = lib
#CONFIG += staticlib
QT += core
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
