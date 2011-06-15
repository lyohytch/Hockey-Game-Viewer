#-------------------------------------------------
#
# Project created by QtCreator 2011-03-23T11:20:55
#
#-------------------------------------------------

QT       += core gui network

TARGET = viewer
TEMPLATE = app


SOURCES += main.cpp\
        gameviewer.cpp \
    gameviewersettings.cpp

HEADERS  += gameviewer.h \
    gameviewersettings.h

FORMS    += gameviewer.ui

DESTDIR = ../build/bin

INCLUDEPATH += . \
               .. \
               ../Domain/includes \
               ../Domain/Operations \
               ../Platforms/KhlRu/Downloader \
               ../Platforms/KhlRu/Parser \
               ../Platforms/KhlRu/Reader \
               ../Presenter

MOC_DIR = ../build/mocs/$$TARGET
OBJECTS_DIR = ../build/objs/$$TARGET

QT += xmlpatterns
LIBS += -L../build/bin -lpresenter -lkhlru -loperations

RESOURCES += ../resources.qrc

## CONFIG settings(debug)
CONFIG(release, debug|release): DEFINES += QT_NO_DEBUG QT_NO_DEBUG_OUTPUT QT_NO_WARNING_OUTPUT

## CONFIG settings (release)
#CONFIG += release
#CONFIG -= debug
#DEFINES += QT_NO_DEBUG QT_NO_DEBUG_OUTPUT QT_NO_WARNING_OUTPUT
