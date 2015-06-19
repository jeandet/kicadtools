#-------------------------------------------------
#
# Project created by QtCreator 2015-06-11T21:37:25
#
#-------------------------------------------------

QT       += core gui opengl
CONFIG += qilib

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = PCBView
TEMPLATE = app

MOC_DIR      = moc
RCC_DIR      = resources
OBJECTS_DIR  = obj
DESTDIR      = ../../bin

INCLUDEPATH += $$top_builddir/../../qilib \
                    $$top_srcdir/../../qilib

LIBS += -L../../bin -lQIlib

SOURCES += main.cpp\
        mainwindow.cpp \
    pcbgraphicview.cpp \
    pcbmodule.cpp \
    pcbline.cpp \
    pcbcontext.cpp \
    pcbvia.cpp \
    pcbpad.cpp \
    pcbzone.cpp

HEADERS  += mainwindow.h \
    pcbgraphicview.h \
    pcbmodule.h \
    pcbline.h \
    pcbcontext.h \
    pcbvia.h \
    pcbpad.h \
    pcbzone.h

FORMS    += mainwindow.ui
