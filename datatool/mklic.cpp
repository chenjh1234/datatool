#include "ckUser.h"

main()
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
    string user,sdt1,sdt2;
    QDate dt,dt1;
    dt = QDate::currentDate();
    dt1 = dt.addDays(LIC_TEST_DAYS);
    sdt1 = qToStr(getDateStr(dt.year(),dt.month(),dt.day()));
    sdt2 = qToStr(getDateStr(dt1.year(),dt1.month(),dt1.day()));
    nid.licToFile(mp[LIC_USER],mp[LIC_MID],sdt1,sdt2);

    //nid.licToFile();

}


