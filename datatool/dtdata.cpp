#include <dtdata.h>
#include <dtapp.h>
dtData::dtData()
{
   init();

}
//-----------------
dtData::~dtData()
{

   delete devIn;
   delete devOut;
   delete sumIn;
   delete sumOut;
   delete sumAll;

   delete logS;
   delete logJ;
}
//----------------------------------
void dtData::init()
{
   QString str;
   //m_dataName = "";
   // m_dataType = 0;
   // char ch[256];

   devIn = new DEV();
   devOut = new DEV();
   sumIn = new sumInfo();
   sumOut = new sumInfo();
   sumAll = new sumInfo();
   logJ = new logFile();
   logS = new logFile();
   //strcpy(ch,fileAppLog().Q2CH);
   //logS->setName(ch);
   str = fileAppLog();
   logS->setName(str);
   qDebug() <<  "end init of data";
   logS->tline("DataTool Started");

   //btStop = false;

}
int dtData::checkDev()
{
   QString str1, str2, str,dfile;
   QString err;
   QFile f;
   int ir;
   ir = 0;
//in:
   str = devIn->name;
   if (devIn->type == DEV_TPIMG)
   {
      str = dataIO::tpimgDFile(str);
      dfile = str;
      if (!canOpen(str))
      {
         err  = "devIn error";
         qDebug() << err;
         ir = OPEN_READ_ERR;
      }
      str = dataIO::tpimgIFile(str);
      if (!canOpen(str))
      {
         err  = "devIn error";
         qDebug() << err;
         ir = OPEN_READ_ERR;
      }
      devIn->size = fileSize(dfile);
   }
   if (devIn->type == DEV_TAPE)
   {
      if (!canOpen(str))
      {
         err  = "devIn error";
         qDebug() << err;
         ir = OPEN_READ_ERR;
      }
   }
   if (devIn->type == DEV_DISK)
   {
      // check format:
   }
   if (ir != 0) return ir;



   //out:

   str1 = "file:" + devOut->name + "in Exist !";
   str2 = "Overide or not?";
   str  = devOut->name;
   if (devOut->type == DEV_TPIMG)
   {
      str = dataIO::tpimgDFile(str);
      // dfile
      qDebug() << "dfile = " << str;
      if (isFile(str)) if (!WIN->askDlg(str1, str2)) ir = OPEN_WRITE_ERR;
#if 0
      // ifile
      str = dataIO::tpimgIFile(str);
      qDebug() << "ifile = " <<str;
      if(isFile(str))
      if(WIN->askDlg(str1,str2))
      ir = OPEN_WRITE_ERR;
#endif
   }
   if (devOut->type == DEV_DISK)
   {
      //str = dataIO::tpimgIFile(str);
      qDebug() << "disk file = " << str;
      if (isFile(str)) if (!WIN->askDlg(str1, str2)) ir = OPEN_WRITE_ERR;
   }
   return ir;
}
#if 0
int dtData::saveTapeConfig(QList<QStringList> sllist)
{
   QFile f;
   QString s,str,de,comm;
   int i;
   
   s = fileTapeConfig();
   comm = TAPE_COMM;
   de = " ";
   return saveMsgToFile(s,de,sllist,comm);

}
#endif

int dtData::saveTapeConfig( QStringList slist)
{
   QFile f;
   QString s;//,str;
   //int i;
   s = fileTapeConfig();
   qDebug() << "tape config =" << s;
   return saveListToFile(s,slist);
    
}
#if 0
QLIst<QStringList> dtData::getTapeConfig()
{
   QFile f;
   QString de;
   QStringList slist;
   QLIst<QStringList> sllist

   s = fileTapeConfig();
   de = " ";
   sllist = getMsgFromFile(s,de);
   return sllist;
}
#endif
QStringList dtData::getTapeConfig()
{
   QFile f;
   QString str,s;
   QStringList slist;

   s = fileTapeConfig();
   //qDebug() << "tconf = " << s;
   return getListFromFile(s);

#if 0
   f.setFileName(s);
   if (f.open(QIODevice::ReadOnly |QIODevice::Text )) 
   {
       QTextStream in(&f);     
       do
       {
           in >> str;
           if (str[0] == "#") continue;          
           if (str.isNull())
               slist << str; 

       }while(!str.isNull());
       f.close();
   }
   return slist; 
#endif
}
QString dtData::getLicConfig()
{
   QFile f;
   QString s,str;
   QString slist;
   
   s = fileLicConfig();
   f.setFileName(s);
   if (f.open(QIODevice::ReadOnly |QIODevice::Text )) 
   {
       QTextStream in(&f);     
       //do
      // {
           in >> str;
           //if (str.isNull())  
           //    slist << str; 
      // }while(!str.isNull());
       f.close();
   }
   return str; 
}
int dtData::saveLicConfig(QString s)
{
   QFile f;
   QString str;
   int i = -1;
   
   s = fileLicConfig();
   f.setFileName(s);
   if (f.open(QIODevice::WriteOnly |QIODevice::Text |QIODevice::Truncate)) 
   {
       QTextStream out(&f);     
      // for (i =0; i< slist.size(); i++) 
      // {
           str = s ;
           out << str; 
      // } 
       f.close();
       i = 1;
   }
   return i; 
}
QString dtData::getJobNumber()
{
   QFile f;
   QString s,str;
   s = fileJobNumber();
   f.setFileName(s);
   if (f.open(QIODevice::ReadOnly |QIODevice::Text )) 
   {
       QTextStream in(&f);
       in >> str;
       f.close();
   }
   return str; 
}
QString dtData::newJobNumber()
{
   QFile f;
   QString s,str;
   int i;
    
   str = getJobNumber();
   qDebug() << "jobNumber = " <<str;
   i = str.toInt();
   if (i >= 9999) i = 0;
   //
   str = QString("%1").arg(i+1,4,10, QLatin1Char( '0' ));

   s = fileJobNumber();

   f.setFileName(s);
   if (f.open(QIODevice::ReadWrite |QIODevice::Text )) 
   {
       QTextStream out(&f);
       out << str;
       f.close();
   }
    qDebug() << "new jobNumber = " <<str << s;
   return str; 
}
void dtData::sumStart()
{   
   sumIn->clear();
   sumAll->clear();
   sumOut->clear();
}
QString dtData::jobname()
{
   QString reel, inName, outName, jname;
   QFileInfo fi(devIn->name);
   inName = fi.baseName();

   QFileInfo fio(devOut->name);
   outName = fio.baseName();

   QFileInfo fir(devIn->reel);
   reel = fir.baseName();

   jname = inName + "-" + reel + "-" + outName + "-" + newJobNumber() + ".job";
   qDebug() << "job =" << jname;
   return jname;
}
// log:===============================================
QString dtData::logApp()
{
   QString str, str1;
   str1 = QString("JobStart:");
   str =  str1 + strEQ(EQ50 - str1.size()) + STR_LR;
   str +=  strEQ(EQ50) + STR_LR;
   str += QString("   AppName : ") + APP_NAME + STR_LR;
   str += QString("AppVersion : ") + APP_NAME + APP_VERSION + STR_LR;
   _startT = dTime();
   str +=         " StartTime : " + _startT + STR_LR;
   str +=         "  Hostname : " + QString(getenv("HOSTNAME")) + STR_LR;
   str +=         "  Username : " + QString(getenv("USER")) + STR_LR;
   logJ->line(str);
   return str;

}
QString dtData::logJob()
{
   QString str;
   //str = QString("Job message") + STR_EQ50 + endl;
   str = "jobName: " + _jobname +  STR_LR;
   str += "jobPath: " + DOC->fileJobLog(_jobname) +  STR_LR;
   logJ->line(str.Q2CH);

   return str;

}
QString dtData::logDev()
{
   return QString(" ");

}
QString dtData::logInput()
{
   QString str, str1;
   str1 = QString("Device Input message:");
   str = str1 +  strEQ(EQ50 - str1.size()) +  STR_LR;
   str += QString(" name: ") +  devIn->name +  STR_LR;
   if (devIn->type == DEV_DISK) str1 = "FILE";
   if (devIn->type == DEV_TPIMG) str1 = "TPIMG";
   if (devIn->type == DEV_TAPE) str1 = "TAPE";

   str += QString(" type: ") +  str1 +  STR_LR;
   str += QString("   id: ") +  devIn->id +  STR_LR;
   str += QString(" reel: ") +  devIn->reel +  STR_LR;
   str += QString(" size: ") +  str1.number(devIn->size) +  STR_LR;
   logJ->line(str.Q2CH);
   return str;

}
QString dtData::logOutput()
{
   QString str, str1;
   str1 = QString("Device Output message:");
   str =  str1 +  strEQ(EQ50 - str1.size()) +  STR_LR;
   str += QString(" name: ") +  devOut->name +  STR_LR;
   if (devOut->type == DEV_DISK) str1 = "FILE";
   if (devOut->type == DEV_TPIMG) str1 = "TPIMG";
   if (devOut->type == DEV_TAPE) str1 = "TAPE";
   str += QString(" type: ") +  str1 +  STR_LR;
   str += QString("   id: ") +  devOut->id +  STR_LR;
   str += QString(" reel: ") +  devOut->reel +  STR_LR;
   str += QString(" size: ") +  str1.number(devOut->size) +  STR_LR;
   logJ->line(str.Q2CH);
   return str;
}
QString dtData::logCMD()
{
   QString str, str1;
   str1 = QString("Command:");
   str = str1 +  strEQ(EQ50 - str1.size()) +  STR_LR;
   str += "TPIMG copy\n";
   logJ->line(str);
   return str;

}
QString dtData::logStop()
{
   QString str, str1;
   str1 = QString("Stoped by User:");
   str = str1 +  strEQ(EQ50 - str1.size()) +  STR_LR;
   logJ->line(str);
   return str;

}
QString dtData::logPause()
{
   QString str, str1;
   str1 = QString("Paused by User:");
   str = str1 +  strEQ(EQ50 - str1.size()) +  STR_LR;
   str += QString("Paused Time:") + dTime();
   logJ->line(str);
   return str;

}
QString dtData::logGoon()
{
   QString str, str1;
   str1 = QString("Start from Pause by User:");
   str = str1 +  strEQ(EQ50 - str1.size()) +  STR_LR;
   str += QString("Start Time:") + dTime();
   logJ->line(str);
   return str;

}
QString dtData::logF()
{
   QString str;
   int file, record, bytes, recordAll;
   file = sumAll->size();
   record = sumAll->getFiles() - 1;
   bytes = sumAll->getBytes();
   recordAll = sumOut->size() - file;

   str = QString("File: %1 , record: %2 , bytes: %3 , record All: %4").arg(file).arg(record).arg(bytes).arg(recordAll);
   logJ->line(str);
   return str;

}
QString dtData::logEnd()
{
   QString str, str1;
   str1 =  QString("Copy Compelete:");
   str = str1 +  strEQ(EQ50 - str1.size()) +  STR_LR;
   logJ->line(str);
   return str;

}

QString dtData::logJobEnd(QString s)
{
   QString str, str1;
   str1 =  QString("Job Compelete: %1:").arg(s);
   str = str1 +  strEQ(EQ50 - str1.size()) +  STR_LR;
   logJ->line(str);
   return str;
}
QString dtData::logSum()
{
   QString str, str1;
   long h, m, s, all;

   int file, tm, ctm, bytes, record;
   file = sumAll->size();  // files

   str1 = QString("    Job Sumary:");
   str = str1 +  strEQ(EQ50 - str1.size()) +  STR_LR;
   str += QString(" Copy Allfiles: %1").arg(file) +  STR_LR;

   record = sumIn->size() - file - _iEOT;
   tm = sumIn->getTime();
   ctm = sumIn->getCpu();
   bytes = sumIn->getBytes();

   str += QString(" Input  record: %1 , bytes: %2 , time: %3 , cputime: %4\n")
      .arg(record).arg(bytes).arg(tm).arg(ctm);

   record = sumOut->size() - file - _iEOT;

   tm = sumOut->getTime();
   ctm = sumOut->getCpu();
   bytes = sumOut->getBytes();

   str += QString(" output record: %1 , bytes: %2 , time: %3 , cputime: %4\n")
      .arg(record).arg(bytes).arg(tm).arg(ctm);

   all = sumIn->getTime() + sumOut->getTime();
   h = all / 3600;
   m = (all - h * 3600) / 60;
   s = all - h * 3600 - m * 60;

   str += QString("     Copy Time: %1 , S = %2:%3:%4 \n")
      .arg(all).arg(h).arg(m).arg(s);

   all = sumIn->getCpu() + sumOut->getCpu();
   h = all / 3600;
   m = (all - h * 3600) / 60;
   s = all - h * 3600 - m * 60;

   str += QString("      Cpu Time: %1 , S = %2:%3:%4 \n")
      .arg(all).arg(h).arg(m).arg(s);
   str += QString("   Start time : ") + _startT +  STR_LR;
   str += QString("Complete time : ") + dTime() +  STR_LR;
   str += QString(" End of Job  ") +  STR_LR;
   logJ->line(str);

   return str;

}
void dtData::logClose()
{
    logJ->close();
}
//app==========================================
QString dtData::pathApp()
{
   QString s;
   s = APP_PATH;
   if (s.length() == 0)
   {
      s = APP_ENV;
      s = QString(getenv(HOME_ENV)) + MARK_PATH + APP_ENV;
   }
   //mkdir(s);
   return s;
}
QString dtData::pathConfig()
{
   return pathApp() + MARK_PATH + APP_CONFIG;
}

QString dtData::pathLog()
{
   return pathApp() + MARK_PATH + APP_LOG;
}

QString dtData::pathLic()
{
   return pathApp() + MARK_PATH + APP_LIC;
}
void  dtData::mkdir(QString s)
{
   QFileInfo fi(s);
   QDir d;
   if (!fi.exists())
   {
      d.mkpath(s);
   }
}

//project:==================================
QString dtData::pathProject()
{
   QString s;
   s = PROJECT_PATH;
   if (s.length() == 0)
   {
      s = QString(getenv("HOME")) + MARK_PATH + PROJECT_ENV;
   }
   //mkdir(s);
   return s;
}
QString dtData::pathJobLog()
{
   return pathProject() + MARK_PATH + PROJECT_LOG;
}
QString dtData::pathJob()
{
   return pathProject() + MARK_PATH + PROJECT_JOB;
}
QString dtData::pathData()
{
   return pathProject() + MARK_PATH + PROJECT_DATA;
}

//file=======
QString dtData::fileAppLog()
{
   QString s;
   s = pathLog();
   qDebug() << "s =" << s;
   mkdir(s);
   s = s + +MARK_PATH + APP_LOG_FILE;
   return s;
}

QString dtData::fileJobLog(QString f)
{
   QString s;
   s = pathJobLog();
   mkdir(s);
   s = s + +MARK_PATH + f;
   return s;
}
QString dtData::fileJob(QString f)
{
   QString s;
   s = pathJob();
   mkdir(s);
   s = s + +MARK_PATH + f;
   return s;
}
QString dtData::fileTapeConfig()
{
   QString s;
   s = pathConfig() ; 
   mkdir(s);
   s = s + +MARK_PATH + TAPE_CONFIG;
   return s;
}
QString dtData::fileParaConfig()
{
   QString s;
   s = pathConfig() ; 
   mkdir(s);
   s = s + +MARK_PATH + PARA_CONFIG;
   return s;
}
QString dtData::fileLicConfig()
{
   QString s;
   s = pathConfig() ; 
   mkdir(s);
   s = s + +MARK_PATH + LIC_CONFIG;
   return s;
}
QString dtData::fileJobNumber()
{
   QString s;
   s = pathConfig() ; 
   mkdir(s);
   s = s + +MARK_PATH + JOBNUMBER_FILE;
   return s;
}
bool dtData::isFile(QString f)
{
   QFileInfo fi(f);
   //return fi.exists();
   return fi.isFile();

}
bool dtData::isDir(QString f)
{
   QFileInfo fi(f);
   return fi.isDir();

}
bool dtData::canOpen(QString ff)
{
   QFile f(ff);
   return f.open(QIODevice::ReadOnly);
}
qint64 dtData::fileSize(QString s)
{
   QFile f(s);
   if (f.open(QIODevice::ReadOnly))
   {
      return f.size();
   }
   return -1;
}
