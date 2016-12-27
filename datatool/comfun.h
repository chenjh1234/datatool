#ifndef COMFUN_H
#define COMFUN_H

//#include <stringlist>
using namespace std;
#include <sys/types.h>
#include <dirent.h>
//#include <regex.h>
 
#include <string>
#include <iostream>
#include <fstream>
#include <cmath>
#include <ctime>
#include <stdio.h>
#include <vector>
#include <QList>
#include <QString>
#include <QFile>
#include <QDate>
#include <QDateTime>
#include <QFileInfo>
#include <QTextStream>
#include <QStringList>
#define BIN_DIR "/bin"
#define USR_BIN "/usr/bin"
#define TMP_DIR "/tmp"
 

#define NAMELEN_MAX 156
//#define MAX_STR 256
#define FIND_MODE 1
#define ENDL "\n"

typedef vector<string> stringList;
// 2 dimension table :string
/// get message from file 
vector<stringList> getMsgFromFile(string fname,string delimiter);
/// save 
int saveMsgToFile(string fname,string de,vector<stringList> v_slist ,string comm);

// for QString:
/// get lines from file ,and each line contain list of items
QList<QStringList> getMsgFromFile(QString f,QString de );
/// save lines to file ,and each line contain list of items
int saveMsgToFile(QString fname,QString  de,QList<QStringList> v_slist,QString comm);

/// get lines from file
QStringList getListFromFile(QString s);
/// save lines from file
int saveListToFile(QString file,QStringList slist);
int appendListToFile(QString s,QStringList slist);

bool isComm(QString s); // is the string lead by "#"
bool isFile(QString s); // if the file exist,s is the full path"
QString getFileText(QString file);
/// get starded date:20160101
QString getDateStr(int y,int m,int d);
/// if the date turn back 
bool isOverDate();
/// we get newest date in the dir /tmp/usr/bin bin;
QString getlastDate();
 
/**
 * splt srings delimited by space(can be more space )to 
 * stringList 
 * 
 * @author cjh (8/25/2014)
 * 
 * @param str 
 * input str 
 * 
 * @return stringList 
 */
stringList splitStr(string str);
stringList splitStr(string str,const char * dl);
/**
 * merge the stringlist to string by add a space between 
 * strings. 
 * 
 * @author cjh (8/25/2014)
 * 
 * @param list 
 * 
 * @return string 
 */
string mergeStr(stringList list);
string toStr(int i);
string toStr(float i);
string toStr(double i);
string qToStr(QString str );//{ return string(str.toUtf8().data());};
/**
 * find files use "find -maxdepth 1"

 * @param ch : base path;
 * @param filter : like  "*.cpp"
 * 
 * @return stringList 
 */
string rmEndSpace(string s);
string rmEndl(string s);
#endif
