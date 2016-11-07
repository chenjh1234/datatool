#include <iostream>
#include <QDebug>
#include <QtGlobal>
#include <Qt>
#include <QApplication>// if we add it qDebug() cannot work
#include <QDebug>
#include <QDir>
#include "dtapp.h"
#include "dtdata.h"
#include "dtmainwin.h"
#include "ckUser.h"
#include "dtOP.h"
using namespace std;
 
int main(int argc, char *argv[])
{
 
    dtApp app(argc, argv);
    app.setOrganizationName(ORG_NAME);
    app.setApplicationName(APP_NAME);

    dtData doc;
    app.m_doc = &doc;
 
    dtMainWin mainWin;
    app.m_win = &mainWin;
    qDebug() << "app dir = " << app.applicationDirPath() ;
    qDebug() << "working dir = " << QDir::currentPath() ;
#if 1
    
    NodeID id;
    QString f;
    f = doc.fileLicConfig();
    id.setLicPath(f);
    if (!id.isValidUser())
    {
        qDebug() << "No license or License expired!!";
        cout << "No license or License expired!!" << endl;
        exit(1);
    }
#endif
    dtOP wop;
    app.m_op = &wop;
    
 
    mainWin.show();
    return app.exec();
    
} 
