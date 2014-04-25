#==================================================
#
#     _|_|      _|_|_|  _|  _|  _|
#   _|    _|      _|    _|      _|_|_|
#   _|  _|_|      _|    _|  _|  _|    _|
#   _|    _|      _|    _|  _|  _|    _|
#     _|_|  _|  _|_|_|  _|  _|  _|_|_|
#
#==================================================
#
#

QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = QIlib
TEMPLATE = lib

LIBS += -lfl

MOC_DIR      = moc
RCC_DIR      = resources
OBJECTS_DIR  = obj
DESTDIR      = lib

include ( ./parsers/Flex_Bison_FIles/Flex_Bison_FIles.pri )

qilibcfg.path = $$[QT_INSTALL_PREFIX]/mkspecs/features
qilibcfg.files = \
    qilib.prf

target.path = $$[QT_INSTALL_LIBS]

qilibHeaders.path = $$[QT_INSTALL_HEADERS]/QIlib
qilibHeaders.files = \
    qicadnetlist.h \
    qicadpcb.h  \
    qicadlisplikelexique.h

qilibParsersHeaders.path = $$[QT_INSTALL_HEADERS]/QIlib/parsers
qilibParsersHeaders.files = \
    parsers/lispLike_driver.h \
    parsers/lispLike_scanner.h


INSTALLS += target qilibHeaders qilibParsersHeaders qilibcfg

INCLUDEPATH += ./parsers

SOURCES += \
    qicadnetlist.cpp \
    parsers/lispLike_driver.cpp \
    parsers/lispLike_scanner.cpp \
    qicadpcb.cpp \
    qicadlisplikelexique.cpp


HEADERS  += \
    qicadnetlist.h \
    parsers/lispLike_driver.h \
    parsers/lispLike_scanner.h \
    qicadpcb.h \
    qicadlisplikelexique.h

OTHER_FILES += qilib.prf

