TARGET = nhlcom

LIBS += -L../../build/bin -loperations

D = Downloader
P = Parser
R = Reader

QT += network


include (../platforms.pri)
