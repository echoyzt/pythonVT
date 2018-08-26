DISTFILES += manage.py parseheadfile.py collectExcelInfo.py excelCheck_debug.py \
    pythontest.py
QT += widgets
QT += gui
QT += core
FORMS += \
    mainwindow.ui \
    yztfiledialog.ui


HEADERS += \
    mainwindow.h \
    yztfiledialog.h


SOURCES += \
    main.cpp \
    mainwindow.cpp \
    yztfiledialog.cpp

#win32: LIBS += -LC:/ProgramData/Anaconda3/libs/python36.lib
#INCLUDEPATH += C:/ProgramData/Anaconda3/include
#DEPENDPATH += C:/ProgramData/Anaconda3/include


LIBS += C:/ProgramData/Anaconda3/libs/python36_d.lib
#LIBS += -LC:/ProgramData/Anaconda3/libs/ -lpython36
INCLUDEPATH += C:/ProgramData/Anaconda3/include/
#DEPENDPATH += $$PWD/C:/ProgramData/Anaconda3/include

#win32:!win32-g++: PRE_TARGETDEPS += $$PWD/C:/ProgramData/Anaconda3/libs/python36.lib
#else:win32-g++: PRE_TARGETDEPS += $$PWD/C:/ProgramData/Anaconda3/libs/libpython36.a
