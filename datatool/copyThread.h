// copyThread.h: interface for the copyThread class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_QCOPYTHREAD_H__4026F176_E9CD_44EA_8BBD_321A4FC384FF__INCLUDED_)
#define AFX_QCOPYTHREAD_H__4026F176_E9CD_44EA_8BBD_321A4FC384FF__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
#include <QThread>
#include "copyITF.h"

class copyThread : public QThread  
{
public:
	copyThread();
	virtual ~copyThread(); 

	void run();
	void init();


	copyITF *m_thcpy;
	void setCopy(copyITF *cpy);

	int m_iReturn;
};

#endif // !defined(AFX_QCOPYTHREAD_H__4026F176_E9CD_44EA_8BBD_321A4FC384FF__INCLUDED_)
