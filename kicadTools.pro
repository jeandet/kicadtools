#================================================================================================
#
#   _|    _|  _|                            _|    _|_|_|_|_|                    _|
#   _|  _|          _|_|_|    _|_|_|    _|_|_|        _|      _|_|      _|_|    _|    _|_|_
#   _|_|      _|  _|        _|    _|  _|    _|        _|    _|    _|  _|    _|  _|  _|_|
#   _|  _|    _|  _|        _|    _|  _|    _|        _|    _|    _|  _|    _|  _|      _|_
#   _|    _|  _|    _|_|_|    _|_|_|    _|_|_|        _|      _|_|      _|_|    _|  _|_|_|
#
#================================================================================================
#
#


TEMPLATE = subdirs
CONFIG   += ordered release

SUBDIRS += qilib \
            test



OTHER_FILES += \
    README.md \
    COPYING