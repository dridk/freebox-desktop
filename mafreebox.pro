#-------------------------------------------------
#
# Project created by QtCreator 2013-07-02T22:40:20
#
#-------------------------------------------------

QT = core gui network widgets

TARGET = freebox-desktop
TEMPLATE = app
ICON = myapp.icns


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

