#include "comfun.h"

bool isComm(QString s)
{ 
    if (s.left(1) == QString("#"))
    return true;
    else return false;
}
QString getFileText(QString s)
{
   QFile f;
   QString str ,rstr;
    
   rstr = "";
   f.setFileName(s);
   if (f.open(QIODevice::ReadOnly |QIODevice::Text )) 
   {
       QTextStream in(&f);     
       do
       {
           str = in.readLine();
           //qDebug() << "read line = " << str << str.isNull() ;
           //if (str.left(1) == QString("#")) continue;          
           //if (!str.isNull())
              rstr +=  str +ENDL ; 
       }while(!str.isNull());
       f.close();
   }
   return rstr; 
}
QStringList getListFromFile(QString s)
{ 
   QFile f;
   QString str;
   QStringList slist;

   f.setFileName(s);
   if (f.open(QIODevice::ReadOnly |QIODevice::Text )) 
   {
       QTextStream in(&f);     
       do
       {
           str = in.readLine();
           //qDebug() << "read line = " << str << str.isNull() ;
           if (str.left(1) == QString("#")) continue;          
           if (!str.isNull())
               slist << str; 

       }while(!str.isNull());
       f.close();
   }
   return slist; 
}
int saveListToFile(QString s,QStringList slist)
{
   QFile f;
   QString str;
   int i;
   f.setFileName(s);
   if (f.open(QIODevice::WriteOnly |QIODevice::Text |QIODevice::Truncate)) 
   {
       QTextStream out(&f);     
       for (i =0; i< slist.size(); i++) 
       {
           str = slist[i];
           //qDebug() << "write = " << str;
           out << str << ENDL; 
       } 
       f.close();
   }
   return i-1; 
}
vector<stringList> getMsgFromFile(string fname,string de )
{
   string str;
   ifstream fin;
//   char chh[256];
   vector<stringList> v_slist;
   stringList slist;
   int MAX_LENGTH = 256;
   char line[MAX_LENGTH];

   fin.open(fname.c_str());
   if (!fin) 
   {
       cout << "open file err :" << fname <<endl;
       return v_slist;
   }
//read:
#if 0
   ifstream fin("tmp.dat");

  int MAX_LENGTH = 100;
  char line[MAX_LENGTH];

  while( fin.getline(line, MAX_LENGTH) ) {
    cout << "read line: " << line << endl;
  }
#endif
   while( fin.getline(line, MAX_LENGTH) ) 
   {
       if (line[0]=='#') continue;
       slist = splitStr(line, de.c_str()); 
       v_slist.push_back(slist);
   }
   fin.close();
// return;
   return v_slist;
}
int saveMsgToFile(string fname,string de,vector<stringList> v_slist,string comm)
{
   string str;
   ofstream fout;
   //char chh[256];
 
   stringList slist;
//   int MAX_LENGTH = 256;
//   char line[MAX_LENGTH];
   fout.open(fname.c_str());
   if (!fout ) 
   {
       cout << "open file for write err :" << fname <<endl;
       return -1;
   }
   int len,i,llen,j;
   len = v_slist.size();
   fout <<"#" << comm <<endl;
   for (i = 0; i < len ; i++)  
   {
       slist = v_slist[i];
       llen = slist.size();
       str = "";
       for (j = 0; j <llen; j++) 
       {
           if (j != llen -1)         
               str = str + slist[j] + de;
           else
               str = str + slist[j];

           
       }
       fout << str <<endl;
   }
   fout.close();
   return len;
}
string rmEndSpace(string str)
{
    int p,ret;
    string s;
    //len = str.length();
    p = 0;
    while (str[p] == ' ')//erase " "
        p++;

    ret = str.find(" ",p); // find  = " "
    if (ret != (int)string::npos)
    {
        s = str.substr(p,ret-p);
    } else
    {
        s = str.substr(p);  
    }
    return s;
}
string rmEndl(string str)
{
    int p,ret;
    string s;
    //len = str.length();
    p = 0;
    s = str;
     
    ret = str.find("\n"); // find  = " "
    if (ret != (int)string::npos)
    {
        s = str.substr(p,ret);
    } 
     
    return s;
}
stringList splitStr(string str)
{
    return splitStr(str," ");
}
stringList splitStr(string str, const char * dl)
{
    int len,p,ret;//,pp;
    string s;
    stringList slist;
    len = str.length();

    p = 0;
    //pp = 0;
    while (1)
    {

        while (str[p] == ' ')//erase " "
            p++;

        ret = str.find(dl,p); // delemiter = "="
        if (ret != (int)string::npos)
        {

            s = str.substr(p,ret-p);
            s = rmEndSpace(s);
            slist.push_back(s); 
            p =ret +1;
            while (str[p] == ' ')//erase " "
            p++;
            //if ( p >= len-1) break;//2014.8.27
            if ( p >= len) break;
        } else
        {
            s = str.substr(p);
            s = rmEndSpace(s);
            //cout << "sizs = " << s.length() << endl;
            s = rmEndl(s);
            //cout << "sizs1 = " << s.length() <<endl;
            slist.push_back(s);
            break;

        }

    }
    return slist;
}
string mergeStr(stringList slist)
{
    int len,i;
    string s;
    len = slist.size();

    for (i = 0 ;i< len ;i++)
    {
        s = s + slist[i] + "=";
    } 
    return s;
}

string toStr(int id)
{
    string str;
    char ch[NAMELEN_MAX];

    sprintf(ch,"%d",id);
    str= ch;
    return str;
}
string toStr(float id)
{
    string str;
    char ch[NAMELEN_MAX];

    sprintf(ch,"%f",id);
    str= ch;
    return str;
}
string toStr(double id)
{
    string str;
    char ch[NAMELEN_MAX];

    sprintf(ch,"%f",id);
    str= ch;
    return str;
}
#if 1
int saveMsgToFile(QString f,QString  de,QList<QStringList> ql_slist,QString comm)
{
    vector<stringList> vslist;
    stringList slist;

    string fn,deli,s,scomm;
    QString qstr;
    int i,j;
    QStringList qslist;
     
    fn = string(f.toUtf8().data());
    deli = string(de.toUtf8().data());
    scomm = string(comm.toUtf8().data());

    for (i = 0; i < ql_slist.size();i++) 
    {
        qslist = ql_slist[i];
        for (j = 0; j < qslist.size();j++)
        {
            qstr = qslist[j];
            s = qstr.toUtf8().data();
            slist.push_back(s);
        }
        vslist.push_back(slist);
    }
    return saveMsgToFile(fn,deli,vslist,scomm);
}
QList<QStringList> getMsgFromFile(QString f,QString de )
{
    vector<stringList> vslist;
    stringList slist;
    string fn,deli,s;
    QString qstr;
    int i,j;
    QStringList qslist;
    QList<QStringList>  listQSlist;
    fn = string(f.toUtf8().data());
    deli = string(de.toUtf8().data());
    vslist = getMsgFromFile(fn,deli);
    for (i = 0; i < (int)vslist.size();i++) 
    {
        slist = vslist[i];
        for (j = 0; j < (int)slist.size();j++)
        {
            s = slist[j];
            qstr = s.c_str();
            qslist << qstr;
        }
        listQSlist << qslist;
    }
    return listQSlist;
};
#endif
#if 0 // test
main()
{
    vector<stringList > vslist;
    cout << "get message from tape.conf========\n";
    vslist = getMsgFromFile("tape.conf"," ");
    cout << "size of tp driver = " << vslist.size() <<endl;
    int j,i;
    for (i = 0; i <vslist.size(); i++) 
    {
        cout << vslist[i].size() << endl;
        for (j = 0; j< vslist[i].size();j++) 
        {
            cout << i<< " " <<j<< " "  << vslist[i][j] << endl;
        }
    }
    cout << "save the  message to tape.conf1========\n";
    saveMsgToFile("tape.conf1"," ",vslist,"# test of save ");

}
#endif
