#ifndef DTAPP_H
#define DTAPP_H

#include <QApplication>
#include "dtmainwin.h"
#include "dtdata.h"
#include "dtOP.h"
#include <iostream>
class dtApp;
class dtData;
//class modMain;


 
using namespace std;
extern dtApp *theApp;
#define DOC theApp->m_doc
#define WIN theApp->m_win
#define WOP theApp->m_op
 
class dtApp :public QApplication  
{
public:
    dtApp( int & argc, char ** argv );
    ~dtApp();
    dtData *m_doc;
    dtMainWin *m_win;
    dtOP *m_op;

private:

};
#endif

