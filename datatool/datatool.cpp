#include <iostream>
#include <QDebug>
#include <QtGlobal>
#include <Qt>
#include <QApplication>// if we add it qDebug() cannot work
#include <QDebug>
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
#if 0
    
    NodeID id;
    if (!id.isValidUser())
    {
        qDebug() << "No license or License expired!!";
        cout << "No license or License expired!!" << endl;
        exit(1);
    }
#endif
    dtData doc;
    app.m_doc = &doc;
 
    dtMainWin mainWin;
    app.m_win = &mainWin;

    dtOP wop;
    app.m_op = &wop;
    
 
    mainWin.show();
    return app.exec();
    
} 
