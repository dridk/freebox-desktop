#-------------------------------------------------
#
# Project created by QtCreator 2013-07-02T22:40:20
#
#-------------------------------------------------

QT       += core gui network

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = mafreebox
TEMPLATE = app



include(api/api.pri)
include(gui/common/common.pri)
include(gui/filesystem/filesystem.pri)

SOURCES += main.cpp\
    mainapplication.cpp

HEADERS  += \
    mainapplication.h

RESOURCES += \
    assets/assets.qrc

