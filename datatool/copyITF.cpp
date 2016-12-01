// copyITF.cpp: implementation of the copyITF class.
//
//////////////////////////////////////////////////////////////////////

#include "copyITF.h"

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

copyITF::copyITF()
{
	init();
}

copyITF::~copyITF()
{
//	delete []m_pcBuf;
}
void copyITF::init()
{
    CP_ERR();
	m_status = "";
	setPause(false);
	setStop(false);
}
void copyITF::wastTime()
{
    //return;

    int i,num,j;
    num = 123456;//6789;
    for (int i = 0; i <num ;i++)
    {
         j = i;
    }
}
QString copyITF::getStatus()
{
	return m_status;
}
void copyITF::setStatus(QString s)
{
	 m_status = s;
}
void copyITF::setPause(bool b)
{
	m_bPause = b;
}

void copyITF::setStop(bool b)
{
	m_bStop = b;
}

void copyITF::setOK()
{
	m_bStop = false;
	m_bPause = false;
}
#if 0
int copyITF::setTape(dataIO *tp)
{
	m_tp = tp;
    //cjhu
	//m_segd.SetTape(m_tp);
	//m_segy.SetTape(m_tp);

	if(m_tp == NULL) return -1;
	else return 0;
}

dataIO * copyITF::getTape()
{
	return m_tp;
}
#endif
#if 0
bool copyITF::IsSelect(int file)
{
	//selection:
	int num,i;
	bool select;

	select = FALSE;

	num = m_data->m_ParSelectRange.size;
	if( num > 0)
	{
		for(i = 0; i < num ; i++)
		{
			if( file >= m_data->m_ParSelectRange.from[i] &&
				file <= m_data->m_ParSelectRange.to[i])
			{
				select = TRUE;
			}
		}
	}
	else
	{
		select = TRUE;
	}
	return select;

}

bool copyITF::IsSelectedAll(int counter)
{
	int num,all;
	bool select;

	select = FALSE;

	num = m_data->m_ParSelectRange.size;
	if( num > 0)
	{
		all =  m_data->m_ParSelectRange.files;
		if( counter >= all)
			select = TRUE;
	}
	else
	{
		select = FALSE;
	}
	return select;	

}
#endif
