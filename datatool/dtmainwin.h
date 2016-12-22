#ifndef DTMAINWIN_H
#define DTMAINWIN_H
#include <QDebug>
#include <QMainWindow>
#include <QSplitter>
#include <QString>
#include <QStringList>
#include <QTabWidget>
#include <QDockWidget>
#include <QTextBrowser>
#include <QProcess>
#include <iostream>
#include <QMenuBar>
#include <QMenu>
#include <QAction>
#include <QToolBar>
#include <QStatusBar>
#include <QFile>
#include <QTextStream>
 
#include <QMdiArea>
#include <QMdiSubWindow>
#include <QSignalMapper>
#include <QLineEdit>
#include <QSlider>
#include <QTreeWidget>


#define LOG_SIZE QSize(700,400)
#define TAPE_SIZE QSize(450,350)
 
#define MOVE_FIRST 0
#define MOVE_LAST 1
#define MOVE_PRE 2
#define MOVE_NEXT 3

#define PARAM_AMP_AGC 44

#define PARAM_NUMBER_OP 10
#define PARAM_NUMBER_LINE 11
 
#define LINEEDIT_WIDTH 32

//#include "dtapp.h"
#include "inputview.h"
#include "copyThread.h"
#include "copyITF.h"
#include "tpimgCopy.h"
#include "editdlg.h"
#include "jobview.h"
#include "paramDlg.h"
#include "anaTape.h"
#include "optionDlg.h"
using namespace std;

class dtMainWin;
//typedef void (CMyClass::*my_handler)(void *arg);
typedef void (dtMainWin::*slotF)();

class dtMainWin : public QMainWindow
{
    Q_OBJECT

public:
    dtMainWin();
    ~dtMainWin();


 
    void openFile(QString file);
    void createActions();
    void createMenus();
    void createToolBars();
    void createStatusBar();

    void readSettings();
    void writeSettings();

    void setTitle();
    int askDlg(QString s);
    int askDlg(QString s1,QString s2);
    void errDlg(QString s);
    void errDlg(QString s1,QString s2);
    void msgOut(QString);
    void msgClear();
    //void addJob(QString);
 
 
    


    QMenu *fileMenu;
    QMenu *locationMenu;
    QMenu *jobMenu;
    QMenu *anaMenu;
    QMenu *helpMenu;
   

    QToolBar *fileToolBar;
    QToolBar *locationToolBar;
    QToolBar *dumpToolBar;
    QToolBar *copyToolBar;
    QToolBar *jobToolBar;
    QToolBar *configToolBar;
    QToolBar *helpToolBar;
    QToolBar *numberToolBar;
  
    QAction *openSegyAct;
    QAction *tapeConfigAct;
    QAction *licConfigAct;
    QAction *jobConfigAct;
    QAction *logConfigAct;
    QAction *optionAct;
 
    QAction *exitAct;

    QAction *moveFirstAct;
    QAction *moveLastAct;
    QAction *movePreAct;
    QAction *moveNextAct;

    QAction *runStartAct;
    QAction *runPauseAct;
    QAction *runStopAct;
   

    QAction *aboutAct;
    QAction *helpAct;

    QLineEdit *agcEdit ;
    copyITF  *getCopy(){return pCopy;};
    anaTape  ana;
    void addAnaTape();
    void addHelp();
    void setStatus(QString str);
    void setEnabledToolbar(QToolBar *,bool b);
    void setOptions();

 
protected:
    void closeEvent(QCloseEvent *event);
    
    
     
    QDockWidget *devDockWidget;
  //  QTabWidget *tabWidget;
   // QDockWidget *modDockWidget;

    QGridLayout *devLay;
    QWidget *devV;
    
    paramDlg *paramD;

    jobView *jobV;
    editDlg *dlgE;

    copyThread *tCopy;
    copyITF  *pCopy;
    optionDlg *option;
    QProcess hrun;
public:
    inputView *inputV,*outputV;
    bool startConform();// not completed
    void runJob();// new a thread, start run job
    void runFile();// start file sum and start Thread; 
    void runThread();// start thread only; 
    void fileEof(); // Eof file sum process; slotFileEnd call it when normal EOF end;
    int endReel(int sta); // for more input file of TPIMG
    int endReelTape(int sta);// for one TPIMG(or tape) which is more reel data;
    void endJob(int );// end of job process;

    int newOutputReel();// copy more reel ,create next file to output:
    /// 0:ok <0 stop;
    int appendReel();// locate the position of the tape wehen parameter append != 0;
    int fromReel();
    int skipReel(dataIO *d,int);
//
    int deviceBT(inputView *v); // open device for ana,dump(open only one device)
    void deviceClose();// close input output device for ana
    int deviceOpen(inputView *v);// open device for copy (open both)
    //void setEnabledToolbar(QToolBar *bar,bool b);

public slots:
    void slotInputBT(); // pressed inputview pushbutton
    void slotOutputBT();//pressed outpouview pushbutton
      
private slots:
   
    void slotOpenFile();
    void slotJobStart();//press runStart button
    void slotJobPause();//press runStart/runContinue button, continue: ->runThread() ; pause:btCom and set flag
    void slotJobStop();//press runStop button : btCom and set flag
    void slotFileEnd(int );//btStarta file compele signal emit( EOF,EOT paused,stopd

    void slotTapeConfig();
    void slotLicConfig();
    void slotOptions();
    //void slotLogConfig();
    void slotLogView(QTreeWidgetItem * , int  );
    //void slotLog(QString);
    void slotJobConfig();
  
 
/**
     * create a compare win,the data is the current data,and 
     * gather. 
     * if a compare win already exist,it will renew the compre 
     * win data ,to the current active data(gather); 
     * 

     * @param  
*/
 
 
    void slotHelp();
    void slotAbout();

    void slotParam(int i);


   // int getDev();
     
    

   
  
private:
  //typedef void (*SLOTF)(); 
    void updateMenus();
    QWidget * createSliderWidget(const QString &text,const QString &tip,int ty,int v,int min,int max,int step);
    QWidget * createSpinWidget(const QString &text,const QString &tip,int ty,int v,int min,int max,int step);
    QWidget *createEditWidget(const QString &text,const QString &tip,int ty,QString v,QLineEdit* &edit);
    QWidget *createEdit2Widget(const QString &text,const QString &tip,const QString &text0,const QString &text1,int ty,QString v,QString v1,QLineEdit *&edit,QLineEdit *&edit1);

    //QAction *  addACT(char *img,char *text,slotF slot);
   // void addACT(QAction *a,char *img,char *text,void * slot);

    QTextEdit *mMain;
    QSignalMapper *windowMapper;
 
 
};
  
#endif


