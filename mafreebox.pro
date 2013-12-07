#-------------------------------------------------
#
# Project created by QtCreator 2013-07-02T22:40:20
#
#-------------------------------------------------

QT = core gui network widgets quick

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
include(gui/call/call.pri)
include(gui/contact/contact.pri)

SOURCES += main.cpp\
    mainapplication.cpp \
    connectionapi.cpp

HEADERS  += \
    mainapplication.h \
    connectionapi.h

RESOURCES += \
    assets/assets.qrc \
    assets/mime.qrc \
    gui/qml.qrc

OTHER_FILES += \
    assets/contributor.html \
    assets/license.html \
    myapp.rc

