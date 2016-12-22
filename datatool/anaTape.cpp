#include "anaTape.h"
#include "dtapp.h"

anaTape::anaTape()
{
   init();
}
void anaTape::init()
{
   dioIn = new dataIO();
   dioOut = new dataIO();
   dio = NULL;
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
   connect(bSkipRAct, SIGNAL(triggered()), this, SLOT(slotBSkipR()));

// bskipf
   bSkipFAct = new QAction(QIcon(":/images/bskipf.png"), tr("backward file"), WIN);
   bSkipFAct->setStatusTip(tr("backward file"));
   connect(bSkipFAct, SIGNAL(triggered()), this, SLOT(slotBSkipF()));

// rewind
   rewindAct = new QAction(QIcon(":/images/rewind.png"), tr("rewind"), WIN);
   rewindAct->setStatusTip(tr("tape rewind"));
   connect(rewindAct, SIGNAL(triggered()), this, SLOT(slotRewind()));
// unload
   unloadAct = new QAction(QIcon(":/images/unload.png"), tr("unload"), WIN);
   unloadAct->setStatusTip(tr("tape unload"));
   connect(unloadAct, SIGNAL(triggered()), this, SLOT(slotUnload()));
// stat
   statusAct = new QAction(QIcon(":/images/status.png"), tr("status"), WIN);
   statusAct->setStatusTip(tr("tape status"));
   connect(statusAct, SIGNAL(triggered()), this, SLOT(slotStatus()));
// copy

   copyfAct = new QAction(QIcon(":/images/copyf.png"), tr("copy file"), WIN);
   copyfAct->setStatusTip(tr("copy file"));
   connect(copyfAct, SIGNAL(triggered()), this, SLOT(slotCopyf()));
// copr

   copyrAct = new QAction(QIcon(":/images/copyr.png"), tr("copy record"), WIN);
   copyrAct->setStatusTip(tr("copy record"));
   connect(copyrAct, SIGNAL(triggered()), this, SLOT(slotCopyr()));
// write eof

   eofAct = new QAction(QIcon(":/images/eof.png"), tr("write eof"), WIN);
   eofAct->setStatusTip(tr("write eof"));
   connect(eofAct, SIGNAL(triggered()), this, SLOT(slotEof()));


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
   //bar->addAction(statusAct);
}
void anaTape::createCopyToolBar(QToolBar *bar)
{
   bar->addAction(copyfAct);
   bar->addAction(copyrAct);
   bar->addAction(eofAct);
   //bar->addAction(statusAct);
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
int anaTape::getOPNumber()
{
   return DOC->opNumber;
}
bool anaTape::isCopyDeviceOpen()
{
   if (!dioIn->isOpen()) if (WIN->deviceOpen(WIN->inputV) < 0) return false;
   if (!dioOut->isOpen()) if (WIN->deviceOpen(WIN->outputV) < 0) return false;
   dio = dioIn;
   return true;

}
void anaTape::deviceClose()
{
   WIN->deviceClose();
}
bool anaTape::isDeviceOpen()
{

   QString st;
   if (!dio->isOpen())
   {
      st = "No device opened!!";
      WIN->msgOut(st);
      return false;
   }
   return true;
}

void anaTape::slotSkipF()
{
   int i, n;
   QString st;
   if (!isDeviceOpen()) return;
   st = "skipF OK";
   n = getOPNumber();
   i = dio->fileForword(n);
   if (i < n) st = QString("skipF ERR ret = %1").arg(i);
   WIN->msgOut(st);
   qDebug() << st;
}
void anaTape::slotSkipR()
{
   int i, n;
   QString st;
   if (!isDeviceOpen()) return;
   st = "skipR OK";
   n = getOPNumber();
   i = dio->recordForword(n);
   if (i < n) st = QString("skipR ERR ret = %1").arg(i);
   WIN->msgOut(st);
   qDebug() << st;
}
void anaTape::slotBSkipF()
{
   int i, n;
   QString st;
   if (!isDeviceOpen()) return;
   st = "back skipF OK";
   n = getOPNumber();
   i = dio->fileBackword(n);
   if (i < n) st = QString("back skipF ERR ret = %1").arg(i);
   WIN->msgOut(st);
   qDebug() << st;
}

void anaTape::slotBSkipR()
{
   int i, n;
   QString st;
   if (!isDeviceOpen()) return;

   st = "back skipR OK";
   n = getOPNumber();
   i = dio->recordBackword(n);
   if (i < n) st = QString("back skipR ERR ret = %1").arg(i);
   WIN->msgOut(st);
   qDebug() << st;
}
void anaTape::slotRewind()
{
   int i;
   QString st;
   if (!isDeviceOpen()) return;
   st = "rewind OK";
   i = dio->rewind();
   if (i == 0) st = "rewind ERR";
   WIN->msgOut(st);
   qDebug() << st;
}
void anaTape::slotUnload()
{
   int i;
   QString st;
   if (!isDeviceOpen()) return;
   st = "unload OK";
   i = dio->unload();
   if (i != 0) st = "unload ERR";
   WIN->msgOut(st);
   qDebug() << st;
}
void anaTape::slotStatus()
{
   int i;
   QString st;
   if (!isDeviceOpen()) return;
   st = "status OK";
   i = dio->status();
   if (i != 0) st = "status ERR";
   WIN->msgOut(st);
   qDebug() << st;
}
void anaTape::slotEof()
{
   int i;
   QString st, stt;
   if (!isCopyDeviceOpen()) return;
   st = "write EOF OK";
   stt = "Write EOF to output device???";
   if (WIN->askDlg(stt))
   {
      i = dioOut->writeEOF();
      if (i < 0) st = "write EOF err";
      WIN->msgOut(st);
      qDebug() << st;
   }
}


void anaTape::slotDump()
{
   int i, n, iret, iby, line;
   QString st;
   st = "OK";
   line = DOC->dumpLines;
   if (!isDeviceOpen()) return;

   iby = DOC->getTapeBlock();
   n = getOPNumber();
   for (i = 0; i < n; i++)
   {
      memset(DOC->buf, '\0', iby);
      iret = dio->read(DOC->buf, iby);
      if (iret == 0)
      {
         if (dio->eotFlag) st = "EOT";
         else st = QString("EOF");
         WIN->msgOut(st);
      }
      else if (iret > 0)
      {
         st = QString("OK,ret = %1\n").arg(iret);
         WIN->msgOut(st);
         st = DOC->hexOut(DOC->buf, iby, line);
         WIN->msgOut(st);
      }
      else
      {
         st = QString("ERR,ret = %1\n").arg(iret);
         WIN->msgOut(st);
      }
   }

   qDebug() << "dump slot";
}
void anaTape::slotDumpOnly()
{

   int iby, line;
   QString st;
   st = "OK";
   line = DOC->dumpLines;
   iby = DOC->getTapeBlock();

   st = QString("dump last read \n");
   WIN->msgOut(st);
   st = DOC->hexOut(DOC->buf, iby, line);
   WIN->msgOut(st);

}
void anaTape::slotCopyf()
{
   int i,n,iret,ifcp;
   QString st,stt;
   if (!isCopyDeviceOpen()) return;
   st = "copyf OK";

   stt = "copy file to output device???";
   if (WIN->askDlg(stt) != 1) return;

   stt = "copy complete ";
   ifcp = 0;

   n = getOPNumber();
   for (i = 0; i < n; i++)
   {
      iret = copyFile();
      qDebug() << " CopyFileEnd st= " << iret ;
      switch (iret) 
      {
      case COPY_EOF:
         st = QString("%1 file copyed, record in file = %2").arg(i+1).arg(lastRecords);
         ifcp = i+1;
         break;
      case COPY_EOT:
          //ifcp = i+1;
         st = QString("%1 end of input device ist = EOT, record in file =%2 ").arg(i+1).arg(lastRecords);
         break;
      case COPY_EOF2:
          ifcp = i+1;
         st = QString("%1 end of input device ist = 2EOF, record in file =%2 ").arg(i+1).arg(lastRecords);
         break;
      default:
          //ifcp = i+1;
         st = QString("copy file err %1, record in file =%2 ").arg(i+1).arg(lastRecords);
        break;
      }
      WIN->msgOut(st);
      if (iret != COPY_EOF) 
          break;
   }// end of for
    st = QString("copy file complete OK : %1 file copyed").arg(ifcp);
    if (iret != COPY_EOF) 
    {
         st = QString("copy file complete: %1 file copyed").arg(ifcp);
    }
    WIN->msgOut(st);
   return;
}
void anaTape::slotCopyr()
{
   int i, n, iret, ircd,iby;
   QString st, stt;
   if (!isCopyDeviceOpen()) return;

   stt = "copy record to output device???";
   if (WIN->askDlg(stt) != 1) return;
   iby = 0;

   n = getOPNumber();
   ircd = 0;
   for (i = 0; i < n; i++)
   {
      iret = copyRecord();
      iby = iret;
      stt = "OK";
//1	eot:
      if (iret == COPY_EOF2 )
      { // end Of Reel;
        //m_iReelCounter ++;
        //DOC->sumFile->addFiles(1);
          stt = "2EOF";
        iby = 0;
      }
      if(iret == COPY_EOT)
      { // end Of Reel;
        //m_iReelCounter ++;
        //DOC->sumFile->addFiles(1);
          stt = "EOT";
         iby = 0;
         break;
      }
//2: eof
//if(m_status == "EOF") //if(iret == COPY_EOF)
      if (iret == COPY_EOF)
      {
         // EOF
         // DOC->sumFile->addFiles(1);
         //break;
          stt = "EOF";
          iby = 0;
      }
      //if (iret != COPY_OK) break;
      ircd = i + 1;
      st = QString("record %1 copyed, len = %2\n").arg(ircd).arg(iby);
      WIN->msgOut(st);
      if (iret == COPY_EOF2 ) break;
      //if(iret == COPY_EOT) break;
   } //end of for
   st = QString("record copy complete with ist = %1,%2 record copyed\n").arg(stt).arg(ircd);
   WIN->msgOut(st);
}
int anaTape::copyRecord()
{
   QString str;
   int iret, ist;
   int iby;
   iby = DOC->getTapeBlock();
   ist = 0;
//read:
//DOC->sumIn->start();
   iret = dioIn->read(DOC->buf, iby);
   //DOC->sumIn->elapsed();
   //DOC->sumIn->addBytes(iret);
   if (iret < 0)
   {
      qDebug() << "read record err ";
      qDebug() << "err = " << dioIn->tpErr[iret];
      ist = COPY_READ_ERR;
      return ist;
   }
   else if (iret == 0)
   {
      //m_status == "EOF";
      if (dioIn->eofFlag) ist = COPY_EOF;
      if (dioIn->eof2Flag) ist = COPY_EOF2;
      if (dioIn->eotFlag) ist = COPY_EOT;
      qDebug() << "copyRecord EOF ist = "<<ist ;
      //eof : continue  to write:
      if (dioIn->eotFlag) return ist; // eot not write
   }
// yes write: data or EOF ,not EOT
   iby = iret;
   //DOC->sumOut->start();
   iret = dioOut->write(DOC->buf, iby);
   //qDebug() << "iret = " <<iret;
   // DOC->sumOut->elapsed();
   //DOC->sumOut->addBytes(iret);

   if (iret < 0)
   {
      qDebug() << "write record err ";
      ist = COPY_WRITE_ERR;
      //return ist;
   }
   else if (iret == 0)
   { //---------we do it in read:
     // m_status == "EOF";
     //ist = COPY_EOF;
   }
   else
       ist = iret;//>0 OK
   return ist;
}
int anaTape::copyFile()
{

   int iret,ir;
   iret = COPY_OK;
   ir = 0;
   while (iret == 0)
   {

      iret = copyRecord();
      ir ++ ;
      if (iret > 0) iret = COPY_OK;
//1	eot:
      if (iret == COPY_EOF2)
      { // end Of Reel;
        //m_iReelCounter ++;
        //DOC->sumFile->addFiles(1);
         break;
      }
      else if (iret == COPY_EOT)
      {
         ir --;
         break;

      }
//2: eof
//if(m_status == "EOF") //if(iret == COPY_EOF)
      else if (iret == COPY_EOF)
      {
         // EOF
         // DOC->sumFile->addFiles(1);
         // ir --;
         break;
      }
      else if (iret < COPY_OK) // err
      {
          ir --;
          break;
      }
   }
   lastRecords = ir;
   return iret;
}
void anaTape::setTapeBlock(int len)
{
   dioIn->setTapeBlock(len);
   dioOut->setTapeBlock(len);
}
