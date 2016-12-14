#ifndef ANA_TAPE_H
#define ANA_TAPE_H

#include <QMenuBar>
#include <QMenu>
#include <QAction>
#include <QToolBar>
#include <QDebug>
#include "QTapeIO.h"
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
    bool isDeviceOpen();
    bool isCopyDeviceOpen();
    int getOPNumber();
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
