#include "dtapp.h"
//#include "dtdata.h"
dtApp *theApp;

#if 0
#define DOC theApp->m_doc
#define WIN theApp->m_win
#define WOP theApp->m_op
#define DRAWVIEW theApp->m_win->drawview;
#endif

dtApp::dtApp( int & argc, char ** argv ):QApplication(argc,argv)
{
    theApp = this;
    m_win = NULL;
}
dtApp::~dtApp()
{
}
