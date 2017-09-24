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
#define APP_VERSION "V1.05"

#if 0
2017.9:v1.05
   1:add h80 FORMAT

2016.12 :v1.04:  
   1: add tape analysis
   2: add  location  toolbars;add dump functions; add selected copy toolbar
   3: add options
   4: add load jobmsgs in jobview that last time down;
2016.12.01:v1.03:  
   1: add append to parameter:n(0: not append,1:append to 1st reel), copy the data to end of output tape device.
   2: add copy from paramters:n(1: from first), which reel start to copy( from input device) .
   3: change mean of copy reel:n(1):copy from multiple reel input device,if n>1 ,copy n reels ,output seprated n files(not a file contain mutiple reels);
2016.11.10:v1.02:  
   1: add tape position parmeter: rewind/unload ,not rewind,before abd finished copy
   2: muiltyple file input , adjust the file position in the fileList
   3:support more tape copy into one, can get a reel from more reel tape;

2016.10.15:v1.01: 
   1: change TAPE_BLOCK = 256000 #define TP_UNLOAD "uld" in QTapeIO.h
   2: add sumStart() in dtdata.cpp     apply in mainwindow::jobrun();
   3: DataIO::read  when DEV_TAPE: # //if (ret != iby) ret =  READFILE_ERR; 
   4: sumInfo::clear()
   5: dtmainwin::runThread() :  add wait(), if thread is runing
   6: runPause,runContinue: add runThread(); fix bugs
   7: jobView : insert jobItem at 0 row not append not work why?
   8:  QTapeIO: add TPF file
#endif
#define APP_DOC "datatool.pdf"
#define SHOW_PDF "evince "
//#define APP_DATE "1.00_2016.09"

#define APP_ENV "DATATOOL" //  app path env
#define APP_PATH getenv(APP_ENV); 
#define APP_CONFIG "etc"       //$DATATOOL/APP_CONFIG
#define APP_LOG "log"       //$DATATOOL/APP_CONFIG
#define APP_LIC "etc"       //$DATATOOL/APP_CONFIG
// config:
//when output device multyple reel(TPIMG) ,if we output to one file ,or serval files:1: a big file ,0:seprated files
#define TPIMG_M_REEL 0

// end
// files:
#define APP_LOG_FILE "datatool.log" 

#define TAPE_CONFIG "tape.conf" //$DATATOOL/etc/tape.conf
#define JOBNUMBER_FILE "job.number" //$DATATOOL/etc/tape.conf
#define PARA_CONFIG "parameters.conf"
#define LIC_CONFIG "datatool.lic"
#define JOBMSG_CONFIG "jobmsg"    //$PROJECT_H/job/jobmsg201605

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
    unsigned char *buf; 
// control:
    //bool btStop;
// log:=====================
    //sumInfo aa;
    QString logApp();   
    QString logJob();
    QString logDev();
    QString logInput();
    QString logOutput();
    QString logAppend(int i);
    QString logFrom(int i);
     
    QString logCMD();
    QString logF();
    QString logReel();// complete a reel;
    QString logNewReel();// for output
    QString logEnd();
    QString logErr(QString s);
    QString logMsg(QString s);
    
    QString logJobEnd(QString s);
    QString logSum();

    QString logStop();
    QString logPause();
    QString logGoon();
    void logClose();

    void sumStart();//clear sums
    QString hexOut( unsigned char *buf,int rby,int line);
    void hexOutStr(char *str,QString &out);// append str with \n
    void hexOutStrN(char *str,QString &out); // append no \n
    int getTapeBlock();
    int setTapeBlock(int i);
 

    logFile *logJ,*logS;
// sum:===================
    sumInfo *sumIn,*sumOut;// sum for input dev,output dev: time,cpu,record,bytes
    sumInfo *sumFile; // sum for copy files  record, bytes 
    sumInfo *sumReel; 
    QString _startT;// job start time
    int _iEOT ; // input type =DISK =0 else 1, when sum all record - iEOT;
    
    //QList<sumInfo> listSum;

//job:======================
    QString jobname();

    QString _jobname;
// dev:=================
    //QString m_dataName;
    //int m_dataType;
    DEV *devIn,*devOut; //device for copy
    QStringList devInFileList;// more input files defined in fileListDlg;
// param:
//#define  PARAM_REWIND_UNLOAD 0
//#define  PARAM_REWIND 1
//#define  PARAM_NOT_REWIND 2

//device position parameters:
// parameters for input dev startcopy or end of copy ,the position of the tape
    int paramInStart,paramInEnd;   
    int paramOutStart,paramOutEnd;
// job paramters :
    int paramCopyFrom;         // copy from which reel (1:defasult)in input device(multyple reel tape device) 
    int paramCopyReels;         // copy reels: default = 1;  input device(multyple reel tape device)  
    int paramCopyAppend;    // default = 0;  where to output,override which reel in  output device( is a big tape)
                            // 0:from start of the tape:
                            // 1:skip first reel (mark 2 eof),output is second reel;
//h80:
    bool _bH80,_bH80SkipTail;
    bool isH80(){return _bH80;};
    void setH80(bool b){_bH80 = b;};
    bool isH80SkipTail(){return _bH80SkipTail;};
    void setH80SkipTail(bool b){_bH80SkipTail = b;};
// next:
   
// options:
    int iTapeBlock;
    bool bCopyToolbar;
    bool bCopyPrompt;
    
//number:
    int opNumber,dumpLines;
    QStringList getDevInFileList(); 
    void setDevInFileList(QStringList list);
    QString getParamStr(int p);
    int  getParamCopyFrom();
    void setParamCopyFrom(int i);
    int  getParamCopyReels();
    void setParamCopyReels(int i);
    int  getParamCopyAppend();
    void setParamCopyAppend(int i);
//
    int  getParamDevInStart();
    void setParamDevInStart(int i);
    int  getParamDevInEnd();
    void setParamDevInEnd(int i);
//
    int  getParamDevOutStart();
    void setParamDevOutStart(int i);
    int  getParamDevOutEnd();
    void setParamDevOutEnd(int i);
    //
    QString getDevPositionStr(int dev);// 0:in,1 :out
    QString getDevInStr();
    QString getDevOutStr();
    QString getCopyParamStr();

    QString getNextName(QString baseName,int id);

 

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
    QString fileJobMsg();
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
    bool isFile(QString f); // is file exist
    bool isDir(QString f); // is a directory
    bool canOpen(QString s); // ia it open for read ok;
    qint64 fileSize(QString f); // filesize;
// dtime:
    QString dTime(){return QDateTime::currentDateTime().toString();};
    // "====" lines od n "="
    QString strEQ(int n){QString str;for(int i=0;i<n;i++) str.append("=");return str;};
   
 
 
};

#endif


