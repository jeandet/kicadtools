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

message(" Check if Flex is installed ")
!system( "flex -V > temp" ){
	error("flex isn't installed, you should install it first or check that it is in the PATH")
	system( $$QMAKE_DEL_FILE $$PWD"/temp" )
}
message(" Success Flex is installed ")
message(" Check if Bison is installed ")
!system( "bison -V > temp" ){
	error("bison isn't installed, you should install it first or check that it is in the PATH")
	system( $$QMAKE_DEL_FILE $$PWD"/temp" )
}
message(" Success Bison is installed ")
system( $$QMAKE_DEL_FILE $$PWD"/temp" )

FLEXSOURCES += \
    $${PWD}/lispLike.l

BISONSOURCES += \
    $${PWD}/lispLike.yy

lispLikeHeaders.path = $$[QT_INSTALL_HEADERS]/QIlib/lispLike
lispLikeHeaders.files = \
    $${DESTDIR}/qilib/lispLike/lispLike.hpp \
    $${DESTDIR}/qilib/lispLike/location.hh \
    $${DESTDIR}/qilib/lispLike/position.hh  \
    $${DESTDIR}/qilib/lispLike/stack.hh

INCLUDEPATH += $${DESTDIR}/..
INSTALLS += lispLikeHeaders

flex.name = Flex
flex.input = FLEXSOURCES
flex.output = ${QMAKE_FILE_BASE}"/lex."${QMAKE_FILE_BASE}.cpp
flex.commands = flex -i -o${QMAKE_FILE_OUT} ${QMAKE_FILE_IN}
flex.variable_out = SOURCES
QMAKE_EXTRA_COMPILERS += flex

bison.name = Bison
bison.input = BISONSOURCES
bison.output = ${QMAKE_FILE_BASE}"/"${QMAKE_FILE_BASE}.cpp
bison.commands = bison -d -o ${QMAKE_FILE_OUT} ${QMAKE_FILE_IN}
bison.CONFIG += target_predeps
bison.variable_out = SOURCES
QMAKE_EXTRA_COMPILERS += bison

OTHER_FILES += \
    $$BISONSOURCES \
    $$FLEXSOURCES




