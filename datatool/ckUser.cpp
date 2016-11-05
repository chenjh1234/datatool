
#include "ckUser.h"
#if  !defined(WIN32)
#include "openssl/md5.h"
#else
#include "md5.h"
void MD5(const unsigned char * ch,int   len, void *buf)
{ 
    MMD5 md5(ch,len);
    memcpy(buf,md5.digest(),16);
};
#endif

#include <fstream>
NodeID::NodeID()
{
    licFile = "";
}
int NodeID::getFileID(string fn)
{
   struct stat buf;
   char *filen;
   int ia;
   filen = (char *)fn.c_str();

   stat(filen, &buf);
   ia = (unsigned int)buf.st_ino;
   //printf("/usr/bin/startx = %08X\n",ia);

   return ia;
}
int NodeID::getFileTID(string fn)
{
   struct stat buf;
   char *filen;
   int ia;
   filen = (char *)fn.c_str();

   stat(filen, &buf);
   int tc[2];
   long long lt  = buf.st_mtime;

   memcpy(tc, &lt, 8);
   return tc[0] + tc[1];
 
}
string NodeID::getMID()
{
   int i;
   string str;
   char ch[256], filen[256];
   int j;

   NodeID dd;
   //: /usr/bin/startx
   j = 0;
   filen[j] = '/'; j++;
   filen[j] = 'u'; j++;
   filen[j] = 's'; j++;
   filen[j] = 'r'; j++;
   filen[j] = '/'; j++;
   filen[j] = 'b'; j++;
   filen[j] = 'i'; j++;
   filen[j] = 'n'; j++;
   filen[j] = '/'; j++;
   filen[j] = 's'; j++;
   filen[j] = 't'; j++;
   filen[j] = 'a'; j++;
   filen[j] = 'r'; j++;
   filen[j] = 't'; j++;
   filen[j] = 'x'; j++;
   filen[j] = 0; j++;

   i = dd.getFileID(filen);
   sprintf(ch, "%08X", i);
   nid1 = ch;
   str = str + ch;

   //: /usr/bin/yum
   j = 0;
   filen[j] = '/'; j++;
   filen[j] = 'u'; j++;
   filen[j] = 's'; j++;
   filen[j] = 'r'; j++;
   filen[j] = '/'; j++;
   filen[j] = 'b'; j++;
   filen[j] = 'i'; j++;
   filen[j] = 'n'; j++;
   filen[j] = '/'; j++;
   filen[j] = 'y'; j++;
   filen[j] = 'u'; j++;
   filen[j] = 'm'; j++;
   filen[j] = 0; j++;
   i = dd.getFileID(filen);
   sprintf(ch, "%08X", i);
   nid2 = ch;
   str = str + ch;
   //:  /sbin/ifconfig
   j = 0;
   filen[j] = '/'; j++;
   filen[j] = 's'; j++;
   filen[j] = 'b'; j++;
   filen[j] = 'i'; j++;
   filen[j] = 'n'; j++;
   filen[j] = '/'; j++;
   filen[j] = 'i'; j++;
   filen[j] = 'f'; j++;
   filen[j] = 'c'; j++;
   filen[j] = 'o'; j++;
   filen[j] = 'n'; j++;
   filen[j] = 'f'; j++;
   filen[j] = 'i'; j++;
   filen[j] = 'g'; j++;
   filen[j] = 0; j++;


   i = dd.getFileID(filen);
   sprintf(ch, "%08X", i);
   nid3 = ch;
   str = str + ch;
   //:  /sbin/ifconfig
   j = 0;
   filen[j] = '/'; j++;
   filen[j] = 's'; j++;
   filen[j] = 'b'; j++;
   filen[j] = 'i'; j++;
   filen[j] = 'n'; j++;
   filen[j] = 0; j++;

   i = dd.getFileTID(filen);
   sprintf(ch, "%08X", i);
   tid = ch;
   str = str + ch;

   //cout << str <<endl;
   return str;
}
void NodeID::setLicPath(QString str)
{
    licFile = string(str.toUtf8().data());
}
void NodeID::setLicPath(string str)
{
    licFile = str;

}
string NodeID::getLicPath()
{
   string str;
   //char *env;
   //env = getenv(LIC_PATH);
   if (licFile.length() == 0)  
   {
#if  !defined(WIN32) 
       str =  string(LIC_PATH) + LIC_FILE; 
#else
       str =  LIC_FILE;

#endif
   }

#if 0
   else
   {
#if  !defined(WIN32) 
       str = string(env) + "/" + LIC_FILE;  
#else
       str =  string(env) + "\\" + LIC_FILE;  
#endif  
   }
#endif // end of 0

   //cout << "lic file = " <<str <<endl;
   return str;
}
map<string,string> NodeID::getLicInfoFromFile()
{
#if  !defined(WIN32)
   string str;
   char chh[256];
   map<string,string> mp;
   stringList strlist;
   char *line=NULL;
   size_t len;
   ssize_t ret;

   int i;
   char *ch;
   ch = (char *)getLicPath().c_str();
   //cout << "file path = " << ch  << endl;
   //cout << "file path len = " << strlen(ch)  << endl;

   //strcpy(chh,"license.dat");
   strcpy(chh,ch);

   FILE *fp = fopen(chh,"rw");
   //cout << "fp = " <<fp <<endl;
   if (fp == NULL)
   {
      cout << "open licfile err" << endl;
      return mp;
   }
   // read msg
   while (ret = getline(&line, &len, fp) != -1)
   {

      i++;
      if (line[0] == '#') continue; // skip command line                       
      str = line;
      //cout << " line = " << line ;
      strlist = splitStr(str,"="); 
      //cout << " line1 = " << strlist[0];
      //cout << " line2 = " << strlist[1];
      mp[strlist[0]] = strlist[1];     
   }
   fclose(fp);
   //cout << "in sub =" << mp[LIC_KEY] <<endl;
   //cout << "in sub =" << mp[LIC_MID] <<endl;
   return mp;
#else
    QStringList listS;
    QString qstr;
    
   string str;
   char chh[256];
   map<string,string> mp;
   stringList strlist;
   char *line=NULL;
   size_t len;
   ssize_t ret;

   int i;
   char *ch;
   ch = (char *)getLicPath().c_str();
   strcpy(chh,ch);
   qstr = chh;
   listS = getListFromFile(qstr);
   int size;
   size =  listS.size();
   for (i = 0; i < size; i++)
   {
       qstr = listS[i];
       if (qstr.left(1) == QString("#")) continue;
       str = qstr.toUtf8().data();
       strlist = splitStr(str,"="); 
       mp[strlist[0]] = strlist[1]; 
       
   }
   return mp;
#endif
}
bool NodeID::isValidUser()
{
    string str,keyF,keyC,mid,sdt;
    time_t lt;
    char dt[256];

    map<string,string> mp;
    mp = getLicInfoFromFile();
    keyF = mp[LIC_KEY]; // key from file:license.dat

    cout << "mp[LIC_KEY] = " << mp[LIC_KEY]  <<endl;
    cout << "mp[LIC_MID] = " << mp[LIC_MID]  <<endl;

    mid = getMID();
    cout << "mid = " <<mid <<endl;
// key:
    //str = mp[LIC_MID] + mp[LIC_USER] + mp[LIC_START] +mp[LIC_END];
    //str = mid + mp[LIC_USER] + mp[LIC_START] +mp[LIC_END]; // mid is the clocal MID
    cout << " mp[LIC_USER] = " << mp[LIC_USER] <<endl;
    cout << " mid = " << mid <<endl;
    cout << " mid = " << mp[LIC_MID] <<endl;
    cout << " mp[LIC_START] = " << mp[LIC_START] <<endl;
    cout << " mp[LIC_END] = " << mp[LIC_END] <<endl;

    keyC = getLic(mp[LIC_USER],mid,mp[LIC_START],mp[LIC_END] );
    cout << "keyC = " << keyC <<endl;
    cout << "keyF = " << keyF <<endl;
    if(keyC != keyF)  return false;
// date expired;
    struct tm *tt;
    time(&lt);
    tt = localtime((const time_t *)&lt);
    sprintf(dt,"%4d%02d%02d",
           tt->tm_year+1900, tt->tm_mon+1, tt->tm_mday);
    cout << "toDay = " << dt << endl;
    cout << "endDay = " << mp[LIC_END] << endl;
    sdt = string(dt);
    if(sdt > mp[LIC_END])  
        return false;
 
    return true;
}
string NodeID::getLic()
{
 
   string str;
   map<string,string> mp;
   mp = getLicInfoFromFile();
   return getLic(mp[LIC_USER], mp[LIC_MID], mp[LIC_START],mp[LIC_END]);
}
string NodeID::getLic(string user,string mid,string start,string end)
{
   string str;
   str =   user+ mid+ start + end;
   return md5Lic(str);

}
void NodeID::licToFile()
{  
   string str;
   map<string,string> mp;
   mp = getLicInfoFromFile();
   licToFile(mp[LIC_USER], mp[LIC_MID], mp[LIC_START],mp[LIC_END]);
}
void NodeID::licToFile(string user,string mid,string start,string end)
{
    string filen,str,key;
    filen = getLicPath();
    ofstream fout;
    fout.open(filen.c_str());

    key = getLic(user,mid,start,end);
    fout << "# license file for user: " << user << endl;
    fout << LIC_USER << LIC_DELIMIT << user << endl;
    fout << LIC_MID << LIC_DELIMIT << mid << endl;
    fout << LIC_START << LIC_DELIMIT << start << endl;
    fout << LIC_END << LIC_DELIMIT << end << endl;
    fout << LIC_KEY << LIC_DELIMIT << key << endl;

    fout.close();
     


}
string NodeID::md5Lic(string s)
{
   string str;
   int i;
   unsigned char md[16];
   char tmp[3] = { '\0' }, buf[41] = { '\0' };

   str = s;
   const unsigned char *data = (unsigned char *)str.c_str();
   unsigned long z;
   z = strlen((char *)data);

   MD5(data, z, md);

   for (i = 0; i < 16; i++)
   {
      //sprintf(tmp,"%2.2x",md[i]);
      sprintf(tmp, "%02X", md[i]);
      strcat(buf, tmp);
      if (i != i / 2 * 2 && i != 15)
      {
         sprintf(tmp, "%1s", "-");
         strcat(buf, tmp);
      }

   }
   //cout << "buf= " << buf << endl;
   str = buf;
   return str;

}
#if 0 // test of lic:
main()
{
   string s;
   char *c;
   NodeID nid;
   s = nid.getMID();
   c = (char *)s.c_str();
   cout << "mid===========================\n";
   cout << "mid = " << c << endl;
   cout << "fid1 = " << nid.nid1 << endl;
   cout << "fid2 = " << nid.nid2 << endl;
   cout << "fid3 = " << nid.nid3 << endl;
   cout << "tid = " << nid.tid << endl;
   cout << "getlic ===========================\n";
   s =  nid.getLic();
   c  = (char *)s.c_str();
   cout << "lic= " << c << endl;

   map<string,string> mp;

   mp = nid.getLicInfoFromFile();
   cout << " getLic Info From File=====================\n";
    for( map<string,string>::iterator iter = mp.begin(); iter != mp.end(); iter++ ) 
    {
        cout << (*iter).first << " = " << (*iter).second <<endl;
    }
    //cout << "mp[string(LIC_KEY)]=" << mp[string(LIC_KEY)] <<endl;
    //cout << "mp[LIC_MID]=" << mp[LIC_MID] <<endl;
    cout << " isValidUser()=====================\n";
    bool b;
    b= nid.isValidUser();

    cout << "is valid = " << b << endl;

    cout << " licToFile()=====================\n";

    nid.licToFile();


}
#endif
ckUser::ckUser()
{
}
QString ckUser::getMid()
{
    string str;
    QString qstr;
    str = nid.getMID();
    qstr = str.c_str();
    return qstr;
}
QString ckUser::getLic()
{
    string str,s;
    QString qstr;
    s = nid.getMID();
    str = nid.md5Lic(s);
    qstr = str.c_str();
    return qstr;
}
QString ckUser::getLic(QString mid)
{
    string str,s;
    QString qstr;
    s = mid.toUtf8().data();//nid.getMID();
    str = nid.md5Lic(s);
    qstr = str.c_str();
    return qstr;
}
void ckUser::regToFile(QString s,QString lic)
{
    QStringList slist;
    QString str;
    str = lic;//getLic();
    slist << str;
    saveListToFile(s,slist);
}
QStringList ckUser::getFromFile(QString s)
{
    QStringList slist;
    QString str;
    str = getLic();
    slist = getListFromFile(s);
    return slist;
}
bool ckUser::isLic(QString f)
{
    QStringList slist;
    QString str;
    int i;
    str = getLic();
    slist = getListFromFile(f);
    for (i = 0; i <slist.size();i++)
    {
        if (slist[i] == str) return true;      
    }
    return false;
}


