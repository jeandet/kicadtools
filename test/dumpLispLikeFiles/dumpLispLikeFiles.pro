QT       += core gui
CONFIG += qilib

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = LispLikeDump
TEMPLATE = app
MOC_DIR      = moc
RCC_DIR      = resources
OBJECTS_DIR  = obj
DESTDIR      = ../../bin

SOURCES += main.cpp

INCLUDEPATH += ../../bin/../../qilib \
                    ../../qilib

message("top_builddir" $$top_builddir)
message("top_srcdir" $$top_srcdir)

LIBS += -L../../bin -lQIlib

FILESTOCOPY.files += \
    $${PWD}/../testFiles/netlist1.net \
    $${PWD}/../testFiles/netlist2.net \
    $${PWD}/../testFiles/pcb1.kicad_pcb\
    $${PWD}/../testFiles/pcb2.kicad_pcb\
    $${PWD}/../testFiles/pcb3.kicad_pcb

FILESTOCOPY.path = $${DESTDIR}

message($${DESTDIR})

defineTest(copyFiles) {
    files = $$1
    DDIR = $$2
    win32:DDIR ~= s,/,\\,g
    QMAKE_POST_LINK += $$QMAKE_MKDIR $$quote($$DDIR) $$escape_expand(\\n\\t)
    for(FILE, files) {
        message(copying file $$FILE to $$DIR)
        # Replace slashes in paths with backslashes for Windows
        win32:FILE ~= s,/,\\,g
        QMAKE_POST_LINK += $$QMAKE_COPY $$quote($$FILE) $$quote($$DDIR) $$escape_expand(\\n\\t)
    }
    export(QMAKE_POST_LINK)
}



!isEmpty(FILESTOCOPY.files) {
                copyFiles($$FILESTOCOPY.files,$$FILESTOCOPY.path)
}



