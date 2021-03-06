DOMAIN_PATH = ../../Domain/

INCLUDEPATH += . \
               .. \
               $$DOMAIN_PATH/includes \
               $$DOMAIN_PATH/Operations

OTHER_FILES += $$DOMAIN_PATH/includes/constants.h \
               $$DOMAIN_PATH/includes/constants_downloader.h
TEMPLATE = lib

QT += core
unix:DESTDIR = ../../build/bin
win32:DESTDIR = ../../build/lib/$$TARGET
win32:DLLDESTDIR = ../../build/bin
MOC_DIR = ../../build/mocs/$$TARGET
OBJECTS_DIR = ../../build/objs/$$TARGET

## CONFIG settings(debug)
CONFIG(release, debug|release): DEFINES += QT_NO_DEBUG QT_NO_DEBUG_OUTPUT QT_NO_WARNING_OUTPUT

## CONFIG settings (release)
#CONFIG += release
#CONFIG -= debug
#DEFINES += QT_NO_DEBUG QT_NO_DEBUG_OUTPUT QT_NO_WARNING_OUTPUT
