// tpimgCopy.h: interface for the tpimgCopy class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_QIMAGECOPYADI_H__0A6CA3C0_5189_4CE7_9160_2B9B1C911B16__INCLUDED_)
#define AFX_QIMAGECOPYADI_H__0A6CA3C0_5189_4CE7_9160_2B9B1C911B16__INCLUDED_
 
//#define TAPE2DISK 0
//#define DISK2TAPE 1

#include "copyITF.h"
 
class tpimgCopy  :public copyITF
{
public:
	bool IsInRange(int id);
	tpimgCopy();
	virtual ~tpimgCopy();
 
	//cjhu QImageADI m_img;


	void init();
	void initCopy();
	int openCopy(DEV in,DEV out);// tape to file
	int copyFile();// main loop of copy file,
	int copyRecord();// main loop of copy record
	int closeCopy();// close copy

};

#endif // !defined(AFX_QIMAGECOPYADI_H__0A6CA3C0_5189_4CE7_9160_2B9B1C911B16__INCLUDED_)
