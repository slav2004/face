#-------------------------------------------------
#
# Project created by QtCreator 2016-09-05T14:35:22
#
#-------------------------------------------------

QT       += core gui

QT += datavisualization

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = face
TEMPLATE = app


SOURCES += main.cpp\
        mainwindow.cpp\
        surfacegraph.cpp

HEADERS  += mainwindow.h\
            surfacegraph.h

FORMS    += mainwindow.ui

RESOURCES += surface.qrc
