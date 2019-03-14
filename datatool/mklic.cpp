#include "ckUser.h"
// file found: 1: datatool.lic  2:/tmp/datatool.lic
#define PASSWD "12345678"
main(int argc ,char **argv)
{
   string s;
   char *c;
   NodeID nid;
#if 0

   s = nid.getMID();
   c = (char *)s.c_str();
   cout << "mid = " << c << endl;

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
#endif
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
    QString pass;
    pass  = "";
    if (argc >1) 
    {
        if (QString(argv[1] )== QString(PASSWD))  
        {
             nid.licToFile();// normal exit
             exit(0);
        }
    }
   //
    mp[LIC_START] = qToStr(nid.today());
    mp[LIC_END] = qToStr(nid.next15Day());
    qDebug() << "to tmp lic=====";
    
    nid. licToFile(mp[LIC_USER], mp[LIC_MID], mp[LIC_START],mp[LIC_END]);
    //nid.licToFile();

}


