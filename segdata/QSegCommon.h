// QSegCommon.h: interface for the QSegCommon class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_QSEGCOMMON_H__62E9411E_5268_4179_90F3_8F43942870C3__INCLUDED_)
#define AFX_QSEGCOMMON_H__62E9411E_5268_4179_90F3_8F43942870C3__INCLUDED_


#include <QString>
#include"QTapeIO.h"
#include<math.h>
#include <QDebug>
//#define TAPE_BLOCK 128000
 
class QSegCommon :public QObject
{
public:

   QSegCommon();
   virtual ~QSegCommon();

   dataIO m_tape,*m_tp,*m_tpo;
   unsigned char m_pcBuf[TAPE_BLOCK];  //buf used when read tape

   /**
   Impormant information in data header
   */
   typedef struct
   {
      int iShot;
      int iTr;
      int iChannel;
      int iType; //1:ok,2:aux
      int iCMP;

      int iLtr;
      int iSi;
      int iOffset;
      int iValid; //1:ok 0:invalid



      float fShotLine;
      float fShotPoint;
      int   iShotIndex;
      float fReceiverLine;
      float fReceiverPoint;
      int   iReceiverIndex;
      int iTrsAll; // all traces in shot
      int iTrs; // seismic traces in shot
      int iAux; //aux traces in shot
   }MAINHD_INFO;

   MAINHD_INFO m_infoMHD;

   int m_iSamples;        //samples of the output of the trace
   int m_iFormat;
   int m_iSI; //us
   int m_iLTR;
   int m_iEndian;

   int m_iIUnit;
   int m_iOUnit; 

   float m_iOSi;
   int m_iOLtr;
   int m_debug;


   QString m_strStatus;

   virtual void Init() {
   };
   void Init0();

   /** get the Endian of the omputer sun:1,pc = 0*/
   int getEndian();
   /** get trace length*/
   int getLtr();
   /** get the sample rate in us*/
   int getSi();
   /** get the data format*/
   int getFormat();
   /** get status of last read */
   QString getStatus();
   /** report status after read */
   void setStatus(QString s);

   //QDiskIO * GetTape();
   //int SetTape(QDiskIO *tp);
/**
    DCB2Int
    @para:
        buf:  pointer 
        i :numbers of the digital(half byte), 
        flag: true:from first halt of the start byte
             false:from last halt of the start byte
*/
   int BCD2Int(unsigned char *buf, int i, bool flag = true);

   /** 1 bytes integer ,one bytes frction*/
   float getFloat16(unsigned char  *p);
   /** get signed int 3 bytes*/
   int getSignedInt3(unsigned char *);
   /** signed int 2 bytes*/
   int getSignedShort(unsigned char *);
   /** unsigned int 3 bytes */
   int getInt3(unsigned char *);
   /** 5 bytes: 3 bytes integer,2 bytes fraction */
   float getSignedFloat32(unsigned char *);

   /** get int   */
   int getInt(unsigned char *buf);
   qint64 getInt64(unsigned char *buf);
   /** get short   */
   int getShort(unsigned char *buf);
   /** get float   */
   float getFloat(void *buf);

   /** set int  */
   int setInt(int *buf, int id);
   /** set short   */
   int setShort(short *buf, short id);

   /**swap each  next two bytes */
   void swap2(unsigned char *buf, int len);
   /**swap each  next four bytes */
   void swap4(unsigned char *buf, int len);
   void swap8(unsigned char *buf, int len);
   /**float to ibm*/
   void float_to_ibm(int from[], int to[], int n);
};

#endif // !defined(AFX_QSEGCOMMON_H__62E9411E_5268_4179_90F3_8F43942870C3__INCLUDED_)
