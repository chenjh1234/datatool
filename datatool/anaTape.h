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
    bool isDeviceOpen();
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
// dataIO:
    dataIO dio;
    DEV dev;

public slots:
    //void slotLocation();
    void slotDump();
    void slotDumpOnly();
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
