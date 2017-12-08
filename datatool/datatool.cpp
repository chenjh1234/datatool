#include <iostream>
#include <QDebug>
#include <QtGlobal>
#include <Qt>
#include <QApplication>// if we add it qDebug() cannot work
#include <QDebug>
#include <QDir>
#include <QTranslator>
#include "dtapp.h"
#include "dtdata.h"
#include "dtmainwin.h"
#include "ckUser.h"
#include "dtOP.h"
using namespace std;
#define HARDWARE_PASSWD "12345678"

int main(int argc, char *argv[])
{
 
    dtApp app(argc, argv);
    app.setOrganizationName(ORG_NAME);
    app.setApplicationName(APP_NAME);
// tralator:
    QTranslator qtTranslator; 
    QString path;
    path = app.applicationDirPath() + "/datatool.qm";
    qtTranslator.load(path); 
    app.installTranslator(&qtTranslator); 

    dtData doc;
    app.m_doc = &doc;
    //doc.getNextName("2222",3);
 
    dtMainWin mainWin;
    app.m_win = &mainWin;
    mainWin.setWindowIcon(QIcon(":/images/tapeicon.png"));
    qDebug() << "app dir = " << app.applicationDirPath() ;
    qDebug() << "working dir = " << QDir::currentPath() ;

#if 1 // for hardware_passwd:
    QString hpass,arg1;
    hpass = HARDWARE_PASSWD;
    arg1 = "";
    if (argc >1) arg1 = argv[1];
    if (arg1 != hpass) 
    {
        qDebug() << "hardware passwd error";
        cout << "hardware passwd error"<< endl;
        exit(1);
    }

#endif
#if 1 // for license:  
    NodeID id;
    QString f;
    f = doc.fileLicConfig();//1:$DATATOOL/etc/datatool.lic, $HOME/DATATOOL/etc/lic
    id.setLicPath(f);
    if (!id.isValidUser())
    {
        qDebug() << "No license or License expired!!";
        cout << "file = " << f.Q2CH << " No license or License expired!!" << endl;
        exit(1);
    }
#endif
    dtOP wop;
    app.m_op = &wop;
    
 
    mainWin.show();
    return app.exec();
    
} 
