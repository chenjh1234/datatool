// copyThread.cpp: implementation of the copyThread class.
//
//////////////////////////////////////////////////////////////////////

#include "copyThread.h"

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

copyThread::copyThread()
{
	init();
}

copyThread::~copyThread()
{

}

void copyThread::init()
{

}
void copyThread::run()
{
	m_iReturn = m_thcpy->copyFile();
}
 
void copyThread::setCopy(copyITF *cpy)
{
	m_thcpy = cpy;
}