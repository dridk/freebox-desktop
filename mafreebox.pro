#-------------------------------------------------
#
# Project created by QtCreator 2013-07-02T22:40:20
#
#-------------------------------------------------

QT       += core gui network

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = mafreebox
TEMPLATE = app

INCLUDEPATH += gui

SOURCES += main.cpp\
        mainwindow.cpp \
    mafreebox.cpp \
    filesystem.cpp \
    download.cpp \
    gui/filesystemmodel.cpp

HEADERS  += mainwindow.h \
    mafreebox.h \
    filesystem.h \
    download.h \
    gui/filesystemmodel.h

FORMS    += mainwindow.ui

OTHER_FILES += \
    path.txt
