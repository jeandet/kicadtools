#-------------------------------------------------
#
# Project created by QtCreator 2015-06-22T23:46:23
#
#-------------------------------------------------

QT       += core gui printsupport

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = QtGuiTests
TEMPLATE = app

MOC_DIR      = moc
RCC_DIR      = resources
OBJECTS_DIR  = obj
DESTDIR      = ../../bin

INCLUDEPATH += $$top_builddir/../../qilib \
                    $$top_srcdir/../../qilib

QMAKE_CXXFLAGS += -fopenmp
QMAKE_LFLAGS += -fopenmp

LIBS += -L../../bin -lQIlib

SOURCES += main.cpp\
        mainwindow.cpp \
    graphicview.cpp \
    polygon.cpp \
    qcustomplot.cpp \
    samplepolygons.cpp

HEADERS  += mainwindow.h \
    graphicview.h \
    polygon.h \
    qcustomplot.h \
    samplepolygons.h

FORMS    += mainwindow.ui

RESOURCES += \
    polygons.qrc
