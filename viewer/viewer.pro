#-------------------------------------------------
#
# Project created by QtCreator 2011-03-23T11:20:55
#
#-------------------------------------------------

QT       += core gui network

TARGET = viewer
TEMPLATE = app


SOURCES += main.cpp\
        gameviewer.cpp

HEADERS  += gameviewer.h

FORMS    += gameviewer.ui

DESTDIR = ../build/bin

INCLUDEPATH += ../IDownload \
               ../IParser \
               ../Presenter \
               ../includes \
               ../IOperation

MOC_DIR = ../build/mocs/$$TARGET
OBJECTS_DIR = ../build/objs/$$TARGET

QT += xmlpatterns
LIBS += -L../build/bin -lpresenter -lparser -ldownloader -lioperation -lrwdata

RESOURCES += ../resources.qrc

## CONFIG settings(debug)
CONFIG += debug
CONFIG -= release
DEFINES += DEBUGING
DEFINES += PROS

## CONFIG settings (release)
#CONFIG += release
#CONFIG -= debug
#DEFINES += QT_NO_DEBUG QT_NO_DEBUG_OUTPUT QT_NO_WARNING_OUTPUT
