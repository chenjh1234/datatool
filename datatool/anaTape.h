#ifndef ANA_TAPE_H
#define ANA_TAPE_H

#include <QMenuBar>
#include <QMenu>
#include <QAction>
#include <QToolBar>
#include <QDebug>
#include "QTapeIO.h"
#include "copyITF.h"
class anaTape :public QObject
{
    Q_OBJECT
public:
    anaTape() ;
    void init();
    void createActions(); 
    void createMenus(QMenu *m);
    void createLocationToolBar(QToolBar *b);
    void createDumpToolBar(QToolBar *b);
    void createCopyToolBar(QToolBar *b);
    bool isDeviceOpen();  // is open foe location,dump dio=== dioIn or dioOut
    bool isCopyDeviceOpen();// is open for copy; dioIn, & dioOut (if not open it)
    int getOPNumber();
    void deviceClose();// close in out 
    int copyRecord();
    int copyFile();
// location:
    QAction *skipFAct;
    QAction *skipRAct;
    QAction *bSkipFAct;
    QAction *bSkipRAct;
    QAction *rewindAct;
    QAction *unloadAct;
    QAction *statusAct;
// dump:
    QAction *dumpAct;
    QAction *dumpOnlyAct;
// copy:
    QAction *copyfAct;
    QAction *copyrAct;
    QAction *eofAct;
// dataIO:
    dataIO *dio,*dioIn,*dioOut;
   // DEV dev;
   // DEV devIn,devOut;
    unsigned char buf[TAPE_BLOCK];
    int lastRecords;// In copyFile function, record copyed in the last call

public slots:
    //void slotLocation();
// dump
    void slotDump();
    void slotDumpOnly();
//copy
    void slotCopyf();
    void slotCopyr();
    void slotEof();

//location
    void slotSkipF();
    void slotSkipR();
    void slotBSkipF();
    void slotBSkipR();
    void slotRewind();
    void slotUnload();
    void slotStatus();
     
private:
    
};
#endif
