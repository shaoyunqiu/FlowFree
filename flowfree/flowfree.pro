#-------------------------------------------------
#
# Project created by QtCreator 2015-08-25T14:42:24
#
#-------------------------------------------------

QT       += core gui
QT += multimedia

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = flowfree
TEMPLATE = app


SOURCES += main.cpp\
        mainwindow.cpp \
    game.cpp \
    funobject.cpp

HEADERS  += mainwindow.h \
    game.h \
    funobject.h

FORMS    += mainwindow.ui

RESOURCES += \
    flowfreemap.qrc
