// tpimgCopy.cpp: implementation of the tpimgCopy class.
//
//////////////////////////////////////////////////////////////////////
#include "dtapp.h"
#include "tpimgCopy.h"
//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

tpimgCopy::tpimgCopy() :
   copyITF()
{
   copyITF::init();
   init();
}

tpimgCopy::~tpimgCopy()
{

}
void tpimgCopy::init()
{
   //Init0();
}

void tpimgCopy::initCopy()
{

}
int tpimgCopy::openIn(DEV in)
{
   int iret;

   // in
   iret = tpIn.openDev(&in, 0);
   if (iret != OPENFILE_OK)
   {
      qDebug() << tpIn.tpErr[iret];
      return OPEN_READ_ERR;
   }
// in start param
   if (in.type == DEV_TAPE) //||in.type ==DEV_TPIMG )
   {
      if (DOC->getParamDevInStart() == PARAM_REWIND)
      {
         tpIn.rewind();
      }
   }
   //DOC->sumReel->start();
   return OPEN_OK;
}
int tpimgCopy::openOut(DEV out)
{
   int iret;

//out
   if (out.type == DEV_TAPE) 
       iret = tpOut.openDev(&out, 2);
   else if(out.type == DEV_TPIMG)
       iret = tpOut.openDev(&out, 1);

   if (iret != OPENFILE_OK)
   {
      qDebug() << tpOut.tpErr[iret];
      return OPEN_WRITE_ERR;
   }
// out start  param
   if (out.type == DEV_TAPE) // ||out.type ==DEV_TPIMG )
   {
      if (DOC->getParamDevOutStart() == PARAM_REWIND)
      {
         tpOut.rewind();
      }
   }
   // ok:
   return OPEN_OK;
}
int tpimgCopy::openCopy(DEV in, DEV out)
{
   int iret;
   initCopy(); // nothoing now

   DOC->sumReel->start();

   iret = openIn(in);
   if (iret != OPEN_OK) return iret;

   iret = openOut(out);
   if (iret != OPEN_OK) return iret;

   // ok:
   return OPEN_OK;
}

int tpimgCopy::copyFile()
{
#if 0 // test of stop; we can catch the stop signal;
   while(1)
   {
      sleep(1);
      if (DOC->btStop)
      {
         qDebug() << "stoped ";
         break;
      }
      else
      qDebug() << " running";
   }
   qDebug() << "out of copyFile ";
   return 0;
#endif
   // qDebug() <<  "start file in copy";
   int iret;
   iret = COPY_OK;
   while (iret == 0)
   {

      iret = copyRecord();

      //qDebug() << " pause = " << WOP->btCMD.isPause();

//1	eot:
      if (iret == COPY_EOF2 || iret == COPY_EOT)
      { // end Of Reel;
        //m_iReelCounter ++;
        //DOC->sumFile->addFiles(1);
         break;
      }
//2: eof
//if(m_status == "EOF") //if(iret == COPY_EOF)
      if (iret == COPY_EOF)
      {
         // EOF
         // DOC->sumFile->addFiles(1);
         break;
      }
//3:pause:
      if (WOP->btCMD.isPause())
      {
         iret = COPY_PAUSE_ERR; //pause; record break to reapond the button
         break;
      }
//4"stop:
      if (WOP->btCMD.isStop())
      {
         iret = COPY_STOP_ERR; //stop;
         break;
      }
// 5:other err;
      if (iret != COPY_OK) break;
   }

   // qDebug() << "end file in copy";
   emit sigFileEnd(iret);

   return iret;
}
/*---------------Write tape-----------;
work:	
    1: readSegd
    2: counter
    3: fill main header
    4: write tape;
return:
    0: ok;
    -1:read error;
    -2: write err;
    -3: end of read(double eof);
    -4: end of write(eot);
    -5: this trace skiped;

*/
int tpimgCopy::copyRecord()
{
   QString str;
   int iret, ist;
   int iby;
   iby = DOC->getTapeBlock();
   ist = 0;
//read:
   DOC->sumIn->start();
   iret = tpIn.read(DOC->buf, iby);
   //wastTime();
   DOC->sumIn->elapsed();
   DOC->sumIn->addBytes(iret);
   if (iret < 0)
   {
      qDebug() << "read record err ";
      qDebug() << "err = " << tpIn.tpErr[iret];
      ist = COPY_READ_ERR;
      return ist;
   }
   else if (iret == 0)
   {
      //m_status == "EOF";
      if (tpIn.eofFlag) ist = COPY_EOF;
      if (tpIn.eof2Flag) ist = COPY_EOF2;
      if (tpIn.eotFlag) ist = COPY_EOT;
      qDebug() << "copyRecord EOF ist = " << cpErr[ist];
      //eof : continue  to write:
      if (tpIn.eotFlag) return ist;// eot not write
   }
// yes write: data or EOF ,not EOT
   iby = iret;
   DOC->sumOut->start();
   iret = tpOut.write(DOC->buf, iby);
   //qDebug() << "iret = " <<iret;
   DOC->sumOut->elapsed();
   DOC->sumOut->addBytes(iret);

   if (iret < 0)
   {
      qDebug() << "write record err ";
      qDebug() << "err = " << tpIn.tpErr[iret];
      ist = COPY_WRITE_ERR;
      //return ist;
   }
   else if (iret == 0)
   { //---------we do it in read:
     // m_status == "EOF";
     //ist = COPY_EOF;
   }
   return ist;
}
/*
========CloseTape=====================
*/
int tpimgCopy::closeIn()
{
   // in end param:
   if (tpIn.getType() == DEV_TAPE) //||in.type ==DEV_TPIMG )
   {
      if (DOC->getParamDevInEnd() == PARAM_REWIND_UNLOAD)
      {
         tpIn.rewind();
         tpIn.unload();
      }
      else if (DOC->getParamDevInStart() == PARAM_REWIND)
      {
         tpIn.rewind();
      }
   }
   tpIn.close();
   //DOC->sumReel->elapsed(); // rell counter:
   return 0;
}
int tpimgCopy::closeOut()
{
   // out end param:
   if (tpOut.getType() == DEV_TAPE) //||in.type ==DEV_TPIMG )
   {
      if (DOC->getParamDevOutEnd() == PARAM_REWIND_UNLOAD)
      {
         tpOut.rewind();
         tpOut.unload();
      }
      else if (DOC->getParamDevOutEnd() == PARAM_REWIND)
      {
         tpOut.rewind();
      }
   }
   tpOut.close();
   return 0;
}
int tpimgCopy::closeCopy()
{
   closeIn();
   closeOut();
   DOC->sumReel->elapsed();
   return 0;
}
#if 0
bool tpimgCopy::IsInRange(int add)
{
   int type;
   bool id = FALSE;
   type = m_data->m_ParSelectRange.type;

   if(type == SELECT_RECORD)
   {
      if(IsSelect(m_iTrCounters))
      id =  TRUE;
   }
   else
   {
      if(IsSelect(m_iFileCounter+add))
      id =  TRUE;
   }
   return id;

}
#endif
