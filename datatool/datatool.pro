######################################################################
# Automatically generated by qmake (3.0) ?? ?? 17 21:34:55 2015
######################################################################
 

TEMPLATE = app
TARGET = datatool
DESTDIR =Debug
CONFIG += debug
QT += widgets 
QT += testlib
!win32 {
        LIBS += -lssl
}
 
 
INCLUDEPATH += .\
        ../segdata


# Input
HEADERS += \
         dtapp.h\
         dtdata.h\
         dtmainwin.h\
         dtOP.h\
         inputview.h\
	 editdlg.h\
	 logfile.h\
         jobview.h\
	 ckUser.h\
	 copyITF.h\
	 tpimgCopy.h\
	 sumInfo.h\
	 copyThread.h\
	 comfun.h\
         md5.h\
	 paramDlg.h\
#	 QTapeData.h\
         ../segdata/QTapeIO.h \
         ../segdata/QSegyADI.h \
         ../segdata/QSegCommon.h 
 

SOURCES += datatool.cpp\ 
         dtapp.cpp\
         dtdata.cpp\
         md5.cpp\
         dtmainwin.cpp\
         dtOP.cpp\
         inputview.cpp\
	 editdlg.cpp\
         jobview.cpp\
	 logfile.cpp\
	 ckUser.cpp\
	 copyITF.cpp\
	 copyThread.cpp\
	 tpimgCopy.cpp\
	 comfun.cpp\
	 sumInfo.cpp\
	 paramDlg.cpp\
#	 QTapeData.cpp\
        ../segdata/QTapeIO.cpp \
        ../segdata/QSegyADI.cpp \
        ../segdata/QSegCommon.cpp 
FORMS += inputoutput.ui\
	paramDlg.ui\
	deviceParam.ui\
	copyParam.ui\
         textedit.ui
RESOURCES     = datatool.qrc
 
