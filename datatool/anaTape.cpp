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
     
    dumpAct = new QAction(QIcon(":/images/readdump.png"), tr("read &dump"), WIN);
    dumpAct->setStatusTip(tr("read and Dump"));
    connect(dumpAct, SIGNAL(triggered()), this, SLOT(slotDump()));

    dumpOnlyAct = new QAction(QIcon(":/images/dumponly.png"), tr("dump"), WIN);
    dumpOnlyAct->setStatusTip(tr(" dump only"));
    connect(dumpOnlyAct, SIGNAL(triggered()), this, SLOT(slotDumpOnly()));

    skipFAct = new QAction(QIcon(":/images/skipf.png"), tr("forward file"), WIN);
    skipFAct->setStatusTip(tr("skip forward file"));
    connect(skipFAct, SIGNAL(triggered()), this, SLOT(slotSkipF()));

    skipRAct = new QAction(QIcon(":/images/skipr.png"), tr("forward record"), WIN);
    skipRAct->setStatusTip(tr("skip forward record"));
    connect(skipRAct, SIGNAL(triggered()), this, SLOT(slotSkipR()));

}

void anaTape::createLocationToolBar(QToolBar *bar)
{
     
   
}
void anaTape::createDumpToolBar(QToolBar *bar)
{
    bar->addAction(dumpAct);
     
   
}
void anaTape::createMenus(QMenu *m)
{
     m->addAction(dumpAct);
   
}
void anaTape::slotDump()
{
    qDebug() << "dump slot";
}
void anaTape::slotLocation()
{

}

