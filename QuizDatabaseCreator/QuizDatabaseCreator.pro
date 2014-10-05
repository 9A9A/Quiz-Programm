#-------------------------------------------------
#
# Project created by QtCreator 2014-09-03T19:02:15
#
#-------------------------------------------------

QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets
QMAKE_CXXFLAGS += -std=c++0x
TARGET = QuizDatabaseCreator
TEMPLATE = app
LIBS += -lCrypto562

SOURCES += main.cpp\
        mainwindow.cpp \
    dialog.cpp

HEADERS  += mainwindow.h \
    dialog.h \
    QuizClassHeader.h

FORMS    += mainwindow.ui \
    dialog.ui
