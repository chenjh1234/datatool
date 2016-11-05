// copyITF.h: interface for the copyITF class.
#ifndef COPY_ITF_H
#define COPY_ITF_H

#include "QTapeIO.h"
//#include "QSegyADI.h"

#define COPY_OK 0
#define COPY_READ_ERR -1
#define COPY_WRITE_ERR -2
#define COPY_DOUBLE_EOF -3
#define COPY_EOT -4
#define COPY_SKIPED -5
#define COPY_PAUSE_ERR -6
#define COPY_STOP_ERR -7
#define COPY_SELECT_ALL -8
#define COPY_EOF -9

#define OPEN_OK 0
#define OPEN_READ_ERR -20
#define OPEN_WRITE_ERR -22
#define OPEN_FILE_INDEX_ERR -23

#define CP_ERR() \
cpErr[COPY_OK] = "OK";\
cpErr[COPY_READ_ERR] = "COPY_READ_ERR";\
cpErr[COPY_WRITE_ERR] = "COPY_WRITE_ERR";\
cpErr[COPY_DOUBLE_EOF] = "COPY_DOUBLE_EOF";\
cpErr[COPY_EOT] = "COPY_EOT";\
cpErr[COPY_SKIPED] = "COPY_SKIPED";\
cpErr[COPY_PAUSE_ERR] = "COPY_PAUSE_ERR";\
cpErr[COPY_STOP_ERR] = "COPY_STOP_ERR";\
cpErr[COPY_SELECT_ALL] = "COPY_SELECT_ALL";\
cpErr[COPY_EOF] = "EOF";\
 \
cpErr[OPEN_OK] = "OK";\
cpErr[OPEN_READ_ERR] = "OPEN_READ_ERR";\
cpErr[OPEN_WRITE_ERR] = "OPEN_WRITE_ERR";\
cpErr[OPEN_FILE_INDEX_ERR] = "OPEN_FILE_INDEX_ERR";\

//#include "sumInfo.h"

//#include "QSegdRead.h"

// copy interface for all copy:
class copyITF  : public QObject
{
	Q_OBJECT  

public:

	copyITF();
	virtual ~copyITF();

 	QString getStatus();
	void setStatus(QString s);
 
	void init();
	void setOK();//slot to clear the pause and stop flag
	void setStop(bool b);//slot of stop button,set stop flag;
	void setPause(bool b);///slot of pause button,set pasue flag;
    void wastTime();
	//bool isSelectedAll(int file);
	//bool isSelect(int counter);

	virtual void snit(){};
	virtual int openCopy(DEV in,DEV out){in.name = ""; out.name = "";return 0;};// tape to file
	virtual int copyFile(){return 0;};// main loop of copy file,
	virtual int copyRecord(){return 0;};// main loop of copy record
	virtual int closeCopy(){return 0;};// close copy

    QMap<int,QString> cpErr;
    QString m_status ;
    dataIO tpIn,tpOut;
    //QSegyADI m_segy;
    //QSegyADI m_segyo;



    bool m_bPause;
    bool m_bStop;


	signals:
	void sigFileEnd(int);

};

#endif // !defined(AFX_QCOPYCOMMONADI_H__647CA606_EEDD_44D6_A59B_2E7CCA32CD19__INCLUDED_)
