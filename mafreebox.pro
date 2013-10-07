#-------------------------------------------------
#
# Project created by QtCreator 2013-07-02T22:40:20
#
#-------------------------------------------------

QT += core gui network
QT +=  webkitwidgets

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = freebox-desktop
TEMPLATE = app
ICON += myappico.png


win32 {
RC_FILE = myapp.rc
}


include(api/api.pri)
include(gui/common/common.pri)
include(gui/filesystem/filesystem.pri)
include(gui/download/download.pri)

SOURCES += main.cpp\
    mainapplication.cpp

HEADERS  += \
    mainapplication.h

RESOURCES += \
    assets/assets.qrc \
    assets/mime.qrc

OTHER_FILES += \
    assets/contributor.html \
    assets/license.html \
    myapp.rc

