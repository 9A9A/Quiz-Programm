#-------------------------------------------------
#
# Project created by QtCreator 2014-08-15T20:20:22
#
#-------------------------------------------------

QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = Quiz_Prgrm
TEMPLATE = app
LIBS += -lCrypto562

SOURCES += main.cpp\
        mainwindow.cpp

HEADERS  += mainwindow.h

FORMS    += mainwindow.ui

win32:CONFIG(release, debug|release): LIBS += -L$$PWD/../../QtCreator/Qt5.3.1_static/lib/ -lCrypto562
else:win32:CONFIG(debug, debug|release): LIBS += -L$$PWD/../../QtCreator/Qt5.3.1_static/lib/ -lCrypto562d

INCLUDEPATH += $$PWD/../../QtCreator/Qt5.3.1_static/include
DEPENDPATH += $$PWD/../../QtCreator/Qt5.3.1_static/include

win32-g++:CONFIG(release, debug|release): PRE_TARGETDEPS += $$PWD/../../QtCreator/Qt5.3.1_static/lib/libCrypto562.a
else:win32-g++:CONFIG(debug, debug|release): PRE_TARGETDEPS += $$PWD/../../QtCreator/Qt5.3.1_static/lib/libCrypto562d.a
else:win32:!win32-g++:CONFIG(release, debug|release): PRE_TARGETDEPS += $$PWD/../../QtCreator/Qt5.3.1_static/lib/Crypto562.lib
else:win32:!win32-g++:CONFIG(debug, debug|release): PRE_TARGETDEPS += $$PWD/../../QtCreator/Qt5.3.1_static/lib/Crypto562d.lib
