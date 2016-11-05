EMPLATE = app
TARGET = mklic
DESTDIR =Debug
CONFIG += debug
QT += widgets 
QT += testlib
!win32 {
        LIBS += -lssl
}
 
# Input
HEADERS += \
        comfun.h\
        md5.h\
	 ckUser.h
 

SOURCES +=  \ 
         mklic.cpp \
         md5.cpp \
         comfun.cpp\
	 ckUser.cpp
