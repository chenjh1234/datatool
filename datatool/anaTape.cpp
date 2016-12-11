#include "anaTape.h"
#include "dtapp.h"

anaTape::anaTape()
{
    init();
}
void anaTape::init()
{
   
}
void anaTape::createActions()
{
// dump     
    dumpAct = new QAction(QIcon(":/images/readdump.png"), tr("read &dump"), WIN);
    dumpAct->setStatusTip(tr("read and Dump"));
    connect(dumpAct, SIGNAL(triggered()), this, SLOT(slotDump()));
// dumponly
    dumpOnlyAct = new QAction(QIcon(":/images/dumponly.png"), tr("dump"), WIN);
    dumpOnlyAct->setStatusTip(tr(" dump only"));
    connect(dumpOnlyAct, SIGNAL(triggered()), this, SLOT(slotDumpOnly()));
// skipf
    skipFAct = new QAction(QIcon(":/images/skipf.png"), tr("forward file"), WIN);
    skipFAct->setStatusTip(tr("skip forward file"));
    connect(skipFAct, SIGNAL(triggered()), this, SLOT(slotSkipF()));
// skipr
    skipRAct = new QAction(QIcon(":/images/skipr.png"), tr("forward record"), WIN);
    skipRAct->setStatusTip(tr("skip forward record"));
    connect(skipRAct, SIGNAL(triggered()), this, SLOT(slotSkipR()));
// bskipr
    bSkipRAct = new QAction(QIcon(":/images/bskipr.png"), tr("backward record"), WIN);
    bSkipRAct->setStatusTip(tr("backward record"));
    connect( bSkipRAct, SIGNAL(triggered()), this, SLOT(slotBSkipR()));

// bskipf
    bSkipFAct = new QAction(QIcon(":/images/bskipf.png"), tr("backward file"), WIN);
    bSkipFAct->setStatusTip(tr("backward file"));
    connect( bSkipFAct, SIGNAL(triggered()), this, SLOT(slotBSkipF()));

// rewind
    rewindAct = new QAction(QIcon(":/images/rewind.png"), tr("rewind"), WIN);
    rewindAct->setStatusTip(tr("tape rewind"));
    connect( rewindAct, SIGNAL(triggered()), this, SLOT(slotRewind()));
// unload
    unloadAct = new QAction(QIcon(":/images/unload.png"), tr("unload"), WIN);
    unloadAct->setStatusTip(tr("tape unload"));
    connect( unloadAct, SIGNAL(triggered()), this, SLOT(slotUnload()));
// stat
    statusAct = new QAction(QIcon(":/images/status.png"), tr("status"), WIN);
    statusAct->setStatusTip(tr("tape status"));
    connect( statusAct, SIGNAL(triggered()), this, SLOT(slotStat()));


}

void anaTape::createLocationToolBar(QToolBar *bar)
{
     bar->addAction(skipFAct);
     bar->addAction(skipRAct);
     bar->addAction(bSkipFAct);
     bar->addAction(bSkipRAct);
     bar->addAction(rewindAct);
     bar->addAction(unloadAct);

   
}
void anaTape::createDumpToolBar(QToolBar *bar)
{
    bar->addAction(dumpAct);
    bar->addAction(dumpOnlyAct);
    bar->addAction(statusAct);
     
   
}
void anaTape::createMenus(QMenu *bar)
{
     bar->addAction(dumpAct);
     bar->addAction(dumpOnlyAct);
     bar->addAction(statusAct);

     bar->addSeparator();

     bar->addAction(skipFAct);
     bar->addAction(skipRAct);
     bar->addAction(bSkipFAct);
     bar->addAction(bSkipRAct);
     bar->addAction(rewindAct);
     bar->addAction(unloadAct);
   
}
void anaTape::slotDump()
{
    if(!isDeviceOpen()) return;
    qDebug() << "dump slot";
}
void anaTape::slotDumpOnly()
{
    if(!isDeviceOpen()) return;
    qDebug() << "dumpOnly slot";
}
void anaTape::slotSkipF()
{
    int i,n;
    QString st;
    if(!isDeviceOpen()) return;
    st = "skipF OK";
    n = 1;
    i = dio.fileForword(n);
    if (i < n)
        st = QString("skipF ERR ret = %1").arg(i);
    WIN->msgOut(st);
    qDebug() << st;
}
void anaTape::slotSkipR()
{
    int i,n;
    QString st;
    if(!isDeviceOpen()) return;
    st = "skipR OK";
    n = 1;
    i = dio.recordForword(n);
    if (i < n)
        st = QString("skipR ERR ret = %1").arg(i);
    WIN->msgOut(st);
    qDebug() << st;
}
void anaTape::slotBSkipF()
{
    int i,n;
    QString st;
    if(!isDeviceOpen()) return;
    st = "back skipF OK";
    n = 1;
    i = dio.fileBackword(n);
    if (i < n)
        st = QString("back skipF ERR ret = %1").arg(i);
    WIN->msgOut(st);
    qDebug() << st;
}
bool anaTape::isDeviceOpen()
{
    
    QString st;
    if(!dio.isOpen())
    {
        st = "No device opened!!";
        WIN->msgOut(st);
        return false;
    }
    return true;
}
void anaTape::slotBSkipR()
{
    int i,n;
    QString st;
    if(!isDeviceOpen()) return;
      
    st = "back skipR OK";
    n = 1;
    i = dio.fileBackword(n);
    if (i < n)
        st = QString("back skipR ERR ret = %1").arg(i);
    WIN->msgOut(st);
    qDebug() << st;
}
void anaTape::slotRewind()
{
    int i,n;
    QString st;
    if(!isDeviceOpen()) return;
    st = "rewind OK";
    n = 1;
    i = dio.rewind();
    if (i == 0)
        st = "rewind ERR";
    WIN->msgOut(st);
    qDebug() << st;
}
void anaTape::slotUnload()
{
    int i,n;
    QString st;
    if(!isDeviceOpen()) return;
    st = "unload OK";
    n = 1;
    i = dio.unload();
    if (i != 0)
        st = "unload ERR";
    WIN->msgOut(st);
    qDebug() << st;
}
void anaTape::slotStatus()
{
    int i,n;
    QString st;
    if(!isDeviceOpen()) return;
    st = "status OK";
    n = 1;
    i = dio.status();
    if (i != 0)
        st = "status ERR";
    WIN->msgOut(st);
    qDebug() << st;
}

