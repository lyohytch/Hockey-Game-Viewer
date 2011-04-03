INCLUDEPATH += ../IDownload \
               ../IParser \
               ../IRWData

QT += network
LIBS += -L../build/bin -lparser -ldownloader -lioperation -lrwdata
