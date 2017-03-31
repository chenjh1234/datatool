 
#ifndef CHECK_USER_H  
#define CHECK_USER_H  

#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <unistd.h>

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include <utime.h>
#include <sys/time.h>
 
#include <map>
#include <iostream>
#include <string>
#include "comfun.h"
//#define FILE1 "/usr/bin/startx"
//#define FILE2 "/usr/bin/yum"
//#define FILE3 "/sbin/ifconfig"
//#define SBIN "/sbin"
#define LIC_FILE "datatool.lic"
#define LIC_PATH  "/tmp/"

#define LIC_USER "user"
#define LIC_MID "mid"
#define LIC_START "start"
#define LIC_END "end"
#define LIC_DELIMIT " = "
#define LIC_TEST_DAYS 15

#define LIC_KEY "key"
using namespace std;
#include <QFile>
#include <QString>
#include "comfun.h"

class NodeID
{
public:
    NodeID();
    unsigned long getFileID(string f);// file node
    int getFileTID(string f);// file create time 
    string getLicPath();// lic file path
    void setLicPath(QString file);// lic file path
    void setLicPath(string file);
    QString today();
    QString nextYear();

    string getMID();// mid of local host
    string getLic();// get key string according to licfile contains;in:(user,mid,start,end ) out(key)
    string getLic(string user,string mid,string start,string end);// calculate lic from parameter;
    void licToFile();// get lic from file and renew the file
    void licToFile(string user,string mid,string start,string end);// get lic and write to file
    bool isValidUser();// is the local host valid ;in{file( user,start,end),getMID()),out(key),and check end > date(now);
    string md5Lic(string str);// get md5 digest od the str;
    map<string,string> getLicInfoFromFile();//get lic file informations( user,mid,start,end,key);
    string nid1,nid2,nid3,tid;// node id of 3 files ,and time of /sbin
    string licFile;


};

class ckUser// no use now
{
public:
    ckUser();
    QString getMid();
    QString getLic();
    QString getLic(QString mid);
    void regToFile(QString s,QString lic);
    QStringList getFromFile(QString s);
    bool isLic(QString f);
    NodeID nid;
};


  
 
#endif  
