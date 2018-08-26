TARGET = VTEC

CONFIG += QTlib
QT	+= network

PRO_cfg = ../../../Project_config
QT_cfg = ../../../Makefile_tpl_qt

# �жϹ��������ļ��Ƿ����
!exists($$PRO_cfg) {
error($$PRO_cfg not exists!)
}
!exists($$QT_cfg) {
error($$QT_cfg not exists!)
}

# �������������ļ�����
include($$PRO_cfg)
include($$QT_cfg)

LIBS += $$QT_LIB_DIR/libOIGL.a -lEC4A -lEC4T -lOIGN

INCLUDEPATH += ../../EC/com/ext/inc ../../EC/com/ext/typ

# Input
HEADERS += *.h
FORMS += *.ui
SOURCES += *.cpp
