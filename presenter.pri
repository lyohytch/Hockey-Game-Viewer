INCLUDEPATH += ../IDownload \
               ../IParser

QT += network
LIBS += -L../build/bin -lparser -ldownloader -lioperation
