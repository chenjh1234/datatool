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
	 ckUser.h\
         comfun.h
 

SOURCES +=  \ 
         mid.cpp \
         comfun.cpp\
	 ckUser.cpp
	 
 

