// tpimgCopy.cpp: implementation of the tpimgCopy class.
//
//////////////////////////////////////////////////////////////////////
#include "dtapp.h"
#include "tpimgCopy.h"
//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

tpimgCopy::tpimgCopy():
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
 
int tpimgCopy::openCopy(DEV in,DEV out)
{
	int iret;
	initCopy();
    // in
    iret = tpIn.openDev(&in,0);
    if(iret !=OPENFILE_OK) 
    {
        qDebug() << tpIn.tpErr[iret];
        return OPEN_READ_ERR ;
    }
    //out
    iret = tpOut.openDev(&out,1);
    if(iret !=OPENFILE_OK) 
    {
        qDebug() << tpOut.tpErr[iret];
        return OPEN_WRITE_ERR ;
    }
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
	while(iret ==0)
	{
         
		iret = copyRecord();
        
        //qDebug() << " pause = " << WOP->btCMD.isPause();
        
//1	eot:	
		if(iret == COPY_DOUBLE_EOF || iret == COPY_EOT)
		{// end Of Reel;
			//m_iReelCounter ++;
            //DOC->sumAll->addFiles(1);
            break;
		}
//2: eof
		//if(m_status == "EOF") //if(iret == COPY_EOF)
        if(iret == COPY_EOF)
		{
            // EOF
           // DOC->sumAll->addFiles(1);
			break;
		}
//3:pause:           
		if(WOP->btCMD.isPause()) 
        {
            iret = COPY_PAUSE_ERR;//pause; record break to reapond the button
            break;
        }
//4"stop:
		if(WOP->btCMD.isStop())  
        {
            iret = COPY_STOP_ERR;//stop;
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
	int iret,ist;
    int iby;
	iby = TAPE_BLOCK;
    ist = 0;
//read:
    DOC->sumIn->start();
    iret = tpIn.read(DOC->buf,iby);
    //wastTime();
    DOC->sumIn->elapsed();
    DOC->sumIn->addBytes(iret);
    if (iret < 0) 
    {
        qDebug() << "read record err " ;
        qDebug() << "err = " <<tpIn.tpErr[iret];
        ist = COPY_READ_ERR;
        return ist;
    }
    else if (iret == 0) 
    {
        //m_status == "EOF";
        if (tpIn.eofFlag) ist = COPY_EOF;
        if (tpIn.eotFlag) ist = COPY_EOT;
        qDebug() << "copyRecord EOT ist = " << cpErr[ist];
        //eof : continue  to write:
    }
// yes write: data or EOF ,EOT
    iby = iret;
    DOC->sumOut->start();
    iret = tpOut.write(DOC->buf,iby);
    DOC->sumOut->elapsed();
    DOC->sumOut->addBytes(iret);

    if (iret < 0) 
    {
        qDebug() << "write record err " ;
        qDebug() << "err = " <<tpIn.tpErr[iret];
        ist = COPY_WRITE_ERR;
        //return ist;
    }
    else if (iret == 0) 
    {//---------we do it in read:
       // m_status == "EOF";
        //ist = COPY_EOF;
    }
	return ist;
}
/*
========CloseTape=====================
*/
int tpimgCopy::closeCopy()
{
    tpIn.close();
    tpOut.close();
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
