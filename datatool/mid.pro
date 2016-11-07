EMPLATE = app
TARGET = mid
DESTDIR =Debug
CONFIG += debug
QT += widgets 
QT += testlib
!win32 {
        LIBS += -lssl
}
 
# Input
HEADERS += \
	 md5.h\
	 ckUser.h\
         comfun.h
 

SOURCES +=  \ 
         mid.cpp \
	 md5.cpp\
         comfun.cpp\
	 ckUser.cpp
	 
 

