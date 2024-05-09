#-------------------------------------------------
#
# Project created by QtCreator 2023-06-18T10:44:33
#
#-------------------------------------------------

QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = SQLDemo
TEMPLATE = app


SOURCES += main.cpp\
        mainwindow.cpp

HEADERS  += mainwindow.h

include(./sqlapi/sqlapi/sqlapi.pri)
INCLUDEPATH += ./sqlapi/sqlapi/
INCLUDEPATH += ../netapi/net

FORMS    += mainwindow.ui
