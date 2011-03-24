#-------------------------------------------------
#
# Project created by QtCreator 2011-03-23T11:20:55
#
#-------------------------------------------------

QT       += core gui

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

LIBS += -L../build/bin -lpresenter -lparser -ldownloader -lioperation
