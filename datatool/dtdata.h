#ifndef DTDATA_H 
#define DTDATA_H 
 
#include <QString>
#include <QMap>
#include <QDebug>
#include <iostream>
#include <QModelIndex>
#include <QWindow>
#include <QScreen>
#include <QFileInfo>
#include <QDir>
#include <QFile>

#define ORG_NAME "DATATOOL"
#define APP_NAME "DataTool"
#define APP_VERSION "V1.01"

/// 2016.10.15:v1.01: change TAPE_BLOCK = 256000 #define TP_UNLOAD "uld" in QTapeIO.h
///    add sumStart() in dtdata.cpp     apply in mainwindow::jobrun();
///    DataIO::read  when DEV_TAPE: # //if (ret != iby) ret =  READFILE_ERR; 
///    sumInfo::clear()
///    dtmainwin::runThread() :  add wait(), if thread is runing
///    runPause,runContinue: add runThread(); fix bugs
///    jobView : insert jobItem at 0 row not append not work why?
///     QTapeIO: add TPF file
#define APP_DOC "datatool.pdf"
#define SHOW_PDF "evince "
//#define APP_DATE "1.00_2016.09"

#define APP_ENV "DATATOOL" //  app path env
#define APP_PATH getenv(APP_ENV); 
#define APP_CONFIG "etc"       //$DATATOOL/APP_CONFIG
#define APP_LOG "log"       //$DATATOOL/APP_CONFIG
#define APP_LIC "etc"       //$DATATOOL/APP_CONFIG
// files:

#define APP_LOG_FILE "datatool.log" 

#define TAPE_CONFIG "tape.conf" //$DATATOOL/etc/tape.conf
#define JOBNUMBER_FILE "job.number" //$DATATOOL/etc/tape.conf
#define PARA_CONFIG "parameters.conf"
#define LIC_CONFIG "datatool.lic"
//#define JOB_NUMBER "job.number"
#if  !defined(WIN32)
#define MARK_PATH "/"
#define HOME_ENV "HOME"
#endif
#if  defined(WIN32)
#define MARK_PATH "\\"
#define HOME_ENV "HOMEPATH"
#endif
// path file
#define PROJECT_ENV "PROJECT_H"
#define PROJECT_PATH getenv(PROJECT_ENV);
#define PROJECT_DATA "data";// 
#define PROJECT_JOB "job";
#define PROJECT_LOG "job";
//#define PROJECT_INFO "job";

#define CONFIG_TAPE "tape.conf"
#define CONFIG_LIC "lic.conf"
 
#define TAPE_COMM "# /dev/st0    3480    500(M) "
// format :
  // in:
#define FMT_SEGD 0
#define FMT_SEGY 1
#define FMT_SEG2 2
  //out usrFormat
#define COPYTO_SEGY 0
#define COPYTO_GRISYS 1
 // realFormat:
#define COPYFMT_TPIMG
#define COPYFMT_D2Y
// param
#define  PARAM_REWIND_UNLOAD 0
#define  PARAM_REWIND 1
#define  PARAM_NOT_REWIND 2

#
#define EQ50 60
#define STR_EQ50 "=================================================="
#define STR_LR "\n"

#include <QFileInfo>
#include <QDebug>



#include "logfile.h"
#include "comfun.h"
#include "sumInfo.h"
#include "copyThread.h"
#include "QTapeIO.h"

class dtData  
{
public:
    dtData();
    ~dtData();
    void init();
// data buf;
    unsigned char buf[TAPE_BLOCK];
// control:
    //bool btStop;
// log:=====================
    //sumInfo aa;
    QString logApp();   
    QString logJob();
    QString logDev();
    QString logInput();
    QString logOutput();
     
    QString logCMD();
    QString logF();
    QString logEnd();
    QString logJobEnd(QString s);
    QString logSum();

    QString logStop();
    QString logPause();
    QString logGoon();
    void logClose();

    void sumStart();//clear sums
 

    logFile *logJ,*logS;
// sum:===================
    sumInfo *sumIn,*sumOut,*sumAll;
    QString _startT;// job start time
    int _iEOT ; // input type =DISK =0 else 1, when sum all record - iEOT;
    //QList<sumInfo> listSum;

//job:======================
    QString jobname();

    QString _jobname;
// dev:=================
    //QString m_dataName;
    //int m_dataType;
    DEV *devIn,*devOut;
// param:
//#define  PARAM_REWIND_UNLOAD 0
//#define  PARAM_REWIND 1
//#define  PARAM_NOT_REWIND 2
    

    int pStartIn,pEndIn;
    int pStartOut,pEndOut,pCopy;


// auto analist file(tape) format // segd,segy...
    int autoFormat(DEV in){ in.name = "" ; return 0;};
    int checkDev();
// toFormat 
    int toFormat ;
// system:
    QString pathApp();
    QString pathConfig();
    QString pathLog();
    QString pathLic();
    void mkdir(QString);
// project:
    QString pathProject();
    QString pathData();
    QString pathJob();
    QString pathJobLog();
// file:
    QString fileAppLog();
    QString fileJobLog(QString f);
    QString fileJob(QString f);
    QString fileTapeConfig();
    QString fileParaConfig();
    QString fileLicConfig();
    QString fileJobNumber();
// config:
    // lic:
    QString getLicConfig();
    int  saveLicConfig(QString s);
    // tape:
    QStringList getTapeConfig();
    int  saveTapeConfig(QStringList s);
    //
    QString getJobNumber();
    QString newJobNumber();

    //QString fileJobData(QDtring f);
    bool isFile(QString f);
    bool isDir(QString f);
    bool canOpen(QString s);
    qint64 fileSize(QString f);
// dtime:
    QString dTime(){return QDateTime::currentDateTime().toString();};
    // "====" lines od n "="
    QString strEQ(int n){QString str;for(int i=0;i<n;i++) str.append("=");return str;};
   
 
 
};

#endif


