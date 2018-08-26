TARGET = VTEC

CONFIG += QTlib
QT	+= network

PRO_cfg = ../../../Project_config
QT_cfg = ../../../Makefile_tpl_qt

# 判断公共配置文件是否存在
!exists($$PRO_cfg) {
error($$PRO_cfg not exists!)
}
!exists($$QT_cfg) {
error($$QT_cfg not exists!)
}

# 包含公共配置文件描述
include($$PRO_cfg)
include($$QT_cfg)

LIBS += $$QT_LIB_DIR/libOIGL.a -lEC4A -lEC4T -lOIGN

INCLUDEPATH += ../../EC/com/ext/inc ../../EC/com/ext/typ

# Input
HEADERS += *.h
FORMS += *.ui
SOURCES += *.cpp
