#include "dtapp.h"
#include "dtmainwin.h"

#include <QSettings>
#include <QMessageBox>
#include <QStandardItemModel>
#include <QModelIndex>
#include <QFileDialog>
#include <QSpinBox>
#include <QLabel>
#include <QToolButton>
#include <QLineEdit>
#include <QDockWidget>
#include <QFileInfo>
#include <QGridLayout>

dtMainWin::dtMainWin() : QMainWindow()
{
   mMain = new QTextEdit(this);
   mMain->setReadOnly(true);

   setCentralWidget(mMain);

   windowMapper = new QSignalMapper(this);

   DOC = theApp->m_doc;

   devDockWidget = new QDockWidget("devView", this);


   addDockWidget(Qt::LeftDockWidgetArea, devDockWidget);
   devDockWidget->setFloating(false);
   devDockWidget->setFixedWidth(300);

   devV = new QWidget(this);

   devLay = new QGridLayout(devV);


   inputV = new inputView(this);
   outputV = new inputView(this, 1);

   connect(inputV->ui.pushButtonCheck, SIGNAL(clicked()), this, SLOT(slotInputBT()));
   connect(outputV->ui.pushButtonCheck, SIGNAL(clicked()), this, SLOT(slotOutputBT()));
   paramD = new paramDlg(this);

   QStringList slist;
   // slist = DOC->getTapeConfig();

   // inputV->setTapes(slist);
   // outputV->setTapes(slist);


   jobV = new  jobView(this);
   connect(jobV, SIGNAL( itemDoubleClicked(QTreeWidgetItem * , int  )), this, SLOT(slotLogView(QTreeWidgetItem * , int  )));



   outputV->setDev("Output");

   devLay->addWidget(inputV, 0, 0);
   devLay->addWidget(outputV, 1, 0);
   devLay->addWidget(jobV, 2, 0);
   devDockWidget->setWidget(devV);

   dlgE = new editDlg(this);
//copy:
   tCopy = new copyThread();
   pCopy = NULL;


   createActions();
   createMenus();
   createToolBars();
   createStatusBar();
   addAnaTape();
   addHelp();

   readSettings();

   setTitle();
   resize(800, 600);
   return;

};
dtMainWin::~dtMainWin()
{
   if (pCopy != NULL) delete pCopy;
   if (tCopy != NULL) delete tCopy;
}

void dtMainWin::errDlg(QString s)
{
   QMessageBox::warning(this, "Error", s);
}
void dtMainWin::errDlg(QString s1, QString s2)
{
   QMessageBox::warning(this, s1, s2);
}

int dtMainWin::askDlg(QString str)
{
   return askDlg("ask:", str);
}

int dtMainWin::askDlg(QString s1, QString s2)
{

   int i;
   i =  QMessageBox::warning(this, s1, s2
                             , QMessageBox::Ok, QMessageBox::Cancel);
   if (i == QMessageBox::Ok) return 1;
   else return 0;

}
void dtMainWin::msgOut(QString s)
{
   qDebug() << "msg = " << s << mMain;
   mMain->append(s);
   DOC->logS->tline(s);
   // mMain->append("\n");
}
void dtMainWin::msgClear()
{
   mMain->clear();
}
#if 0
void dtMainWin::addJob(QString)
{
}
#endif
void dtMainWin::readSettings()
{
   //float f;
   QSettings settings(ORG_NAME, APP_NAME);
   QString str = settings.value("dataname").toString();
   int i = settings.value("datatype").toInt();
   // DOC->m_dataName = str;
   //DOC->m_dataType = i;
}
void dtMainWin::writeSettings()
{
   // setParam();
   QSettings settings(ORG_NAME, APP_NAME);
   //qDebug() << "write setting = " << theApp->m_doc->m_dataName;
   //settings.setValue("dataname", DOC->m_dataName);
   // settings.setValue("datatype", DOC->m_dataType);

}

//void dtMainWin::addACT(QAction *a,char *img,char *text,dtMainWin::SLOTF slot)

#if 0 // test  function pointer
typedef void (*FUN)();
void fun()
{
}
// we try to make a function,but we cannot pass the slot function pointrt????

//void dtMainWin::addACT(QAction *a,char *img,char *text,FUN slot)
QAction * dtMainWin::addACT(char *img,char *text,slotF slot)
{
   //run:
   QAction *a;
   a = new QAction(QIcon(img),tr(text),this);
   qDebug() << a;
   a->setStatusTip(tr(text));
   connect(a, SIGNAL(triggered()), this, SLOT(*slot));
   return a;
}
#endif
//actions============================================

void dtMainWin::createActions()
{
   openSegyAct = new QAction(QIcon(":/images/openfile.png"), tr("OpenSegy"), this);
   openSegyAct->setShortcuts(QKeySequence::Open);
   openSegyAct->setStatusTip(tr("open Segy"));
   connect(openSegyAct, SIGNAL(triggered()), this, SLOT(slotOpenFile()));

   exitAct = new QAction(tr("E&xit"), this);
   exitAct->setShortcuts(QKeySequence::Quit);
   exitAct->setStatusTip(tr("exit the application"));
   connect(exitAct, SIGNAL(triggered()), this, SLOT(close()));
#if 0 // test function pointer
   FUN c;
   c = fun;
#endif
   //slotF c;
   //c = &dtMainWin::slotRunStart;// this is ok
   //c = &slotRunStart; // err
//run:
//addAction(QAction *a,char *img,char *text ,slotFunction *slot)
//addACT(runStartAct,":/images/movefirst.png","runStart",(dtMainWin::SLOTF )&dtMainWin::slotRunStart());
//runStartAct = addACT(":/images/movefirst.png","runStart",&dtMainWin::slotRunStart);
//qDebug() << runStartAct;
//==============================================================================
   runStartAct = new QAction(QIcon(":/images/runstart.png"), tr("runStart"), this);
   //moveFirstAct->setShortcuts(QKeySequence::Quit);
   runStartAct->setStatusTip(tr("runStart"));
   connect(runStartAct, SIGNAL(triggered()), this, SLOT(slotJobStart()));

   runStopAct = new QAction(QIcon(":/images/runstop.png"), tr("runStop"), this);
   //moveFirstAct->setShortcuts(QKeySequence::Quit);
   runStopAct->setStatusTip(tr("runStop"));
   connect(runStopAct, SIGNAL(triggered()), this, SLOT(slotJobStop()));

   runPauseAct = new QAction(QIcon(":/images/runpause.png"), tr("runPause"), this);
   //moveFirstAct->setShortcuts(QKeySequence::Quit);
   runPauseAct->setStatusTip(tr("runPause"));
   connect(runPauseAct, SIGNAL(triggered()), this, SLOT(slotJobPause()));
//config
   tapeConfigAct = new QAction(QIcon(":/images/tapeconfig.png"), tr("tapeConfig"), this);
   //moveFirstAct->setShortcuts(QKeySequence::Quit);
   tapeConfigAct->setStatusTip(tr("tapeConfig"));
   connect(tapeConfigAct, SIGNAL(triggered()), this, SLOT(slotTapeConfig()));

   licConfigAct = new QAction(QIcon(":/images/licconfig.png"), tr("register"), this);
   //moveFirstAct->setShortcuts(QKeySequence::Quit);
   licConfigAct->setStatusTip(tr("register"));
   connect(licConfigAct, SIGNAL(triggered()), this, SLOT(slotTapeConfig()));
#if 0
   logConfigAct = new QAction(QIcon(":/images/logconfig.png"), tr("log"), this);
   //moveFirstAct->setShortcuts(QKeySequence::Quit);
   logConfigAct->setStatusTip(tr("log"));
   connect(logConfigAct, SIGNAL(triggered()), this, SLOT(slotLogConfig()));
#endif
   paraConfigAct = new QAction(QIcon(":/images/paraconfig.png"), tr("paraConfig"), this);
   //moveFirstAct->setShortcuts(QKeySequence::Quit);
   paraConfigAct->setStatusTip(tr("parameters"));
   connect(paraConfigAct, SIGNAL(triggered()), this, SLOT(slotParaConfig()));


//location:
#if 0
   moveFirstAct = new QAction(QIcon(":/images/movefirst.png"), tr("MoveFirst"), this);
   //moveFirstAct->setShortcuts(QKeySequence::Quit);
   moveFirstAct->setStatusTip(tr("move First"));
   connect(moveFirstAct, SIGNAL(triggered()), this, SLOT(slotMoveFirst()));

   moveLastAct = new QAction(QIcon(":/images/movelast.png"), tr("MoveLast"), this);
   //moveFirstAct->setShortcuts(QKeySequence::Quit);
   moveLastAct->setStatusTip(tr("move Last"));
   connect(moveLastAct, SIGNAL(triggered()), this, SLOT(slotMoveLast()));

   movePreAct = new QAction(QIcon(":/images/movepre.png"), tr("MovePre"), this);
   moveFirstAct->setShortcuts(QKeySequence::Back);
   movePreAct->setStatusTip(tr("move Pre"));
   connect(movePreAct, SIGNAL(triggered()), this, SLOT(slotMovePre()));

   moveNextAct = new QAction(QIcon(":/images/movenext.png"), tr("MoveNext"), this);
   moveFirstAct->setShortcuts(QKeySequence::Forward);
   moveNextAct->setStatusTip(tr("move Next"));
#endif

//help:
   aboutAct = new QAction(QIcon(":/images/about.png"), tr("&About"), this);
   aboutAct->setStatusTip(tr("show the application's About box"));
   connect(aboutAct, SIGNAL(triggered()), this, SLOT(slotAbout()));

   helpAct = new QAction(QIcon(":/images/help.png"), tr("&Help"), this);
   helpAct->setStatusTip(tr("Help"));
   connect(helpAct, SIGNAL(triggered()), this, SLOT(slotHelp()));

   qDebug() << "create actions ok";

}
void dtMainWin::addHelp()
{
    helpMenu = menuBar()->addMenu(tr("&Help"));
    helpMenu->addAction(helpAct);
    helpMenu->addAction(aboutAct);

    //help:
    helpToolBar = addToolBar(tr("Help"));
    helpToolBar->addAction(aboutAct);
}

void dtMainWin::createMenus()
{
   fileMenu = menuBar()->addMenu(tr("&File"));
   //fileMenu->addAction(openSegyAct);

   fileMenu->addSeparator();
   fileMenu->addAction(tapeConfigAct);

   //fileMenu->addAction(logConfigAct);
   // fileMenu->addAction(licConfigAct);

   fileMenu->addAction(paraConfigAct);

   fileMenu->addAction(exitAct);


   runMenu = menuBar()->addMenu(tr("&Run"));
   runMenu->addAction(runStartAct);
   runMenu->addAction(runPauseAct);
   runMenu->addAction(runStopAct);
#if 0
   locationMenu = menuBar()->addMenu(tr("&Location"));
   locationMenu->addAction(moveFirstAct);
   locationMenu->addAction(moveLastAct);
   locationMenu->addAction(movePreAct);
   locationMenu->addAction(moveNextAct);
#endif

   qDebug() << "create menu";

}
void dtMainWin::updateMenus()
{

}

void dtMainWin::createToolBars()
{
   QString str;


//location:
#if 0
   locationToolBar = addToolBar(tr("Location"));
   locationToolBar->addAction(moveFirstAct);
   locationToolBar->addAction(moveNextAct);
   locationToolBar->addAction(movePreAct);
   locationToolBar->addAction(moveLastAct);
#endif
//run:
   runToolBar = addToolBar(tr("Run"));
   //qDebug()<< runStartAct;
   runToolBar->addAction(runStartAct);
   runToolBar->addAction(runPauseAct);
   runToolBar->addAction(runStopAct);
   //config:
      configToolBar = addToolBar(tr("Config"));
      //fileToolBar->addAction(openSegyAct);
      //configToolBar->hide();
      configToolBar->addAction(tapeConfigAct);
      configToolBar->addAction(paraConfigAct);


#if 0 //  AGC TEST
   str = "AGC window(ms) 0:no AGC";
   ampToolBar->addWidget(createEditWidget("AGC", str, PARAM_AMP_AGC, "0", agcEdit));
// testToolBar
   testToolBar = addToolBar(tr("Test"));
   str = "Test Slider:0-10";
   testToolBar->addWidget(createSliderWidget("TEST", str, PARAM_TEST, 0, 0, 10, 1));
#endif



}
QWidget* dtMainWin::createEdit2Widget(const QString& text, const QString& tip, const QString& text0, const QString& text1, int ty, QString v, QString v1, QLineEdit *& edit, QLineEdit *& edit1)
{
   QString str;
   str = tip; // "User Scale(H:trs/CM,V:CMs/S)";
   QLineEdit *le = new QLineEdit;
   QLineEdit *le1 = new QLineEdit;
   le->setMaximumWidth(LINEEDIT_WIDTH);
   le1->setMaximumWidth(LINEEDIT_WIDTH);
   le->setText(v);
   le1->setText(v1);
   edit = le;
   edit1 = le1;
   QGridLayout *layout = new QGridLayout;
   QToolButton *tb = new QToolButton();
   tb->setText(text);
   tb->setToolTip(str);
   //tb1->setText(text1);

   layout->addWidget(tb, 0, 0, Qt::AlignCenter);
   //layout->addWidget(new QLabel(text), 0, 0, Qt::AlignCenter);
   layout->addWidget(new QLabel(text0), 0, 1, Qt::AlignCenter);
   layout->addWidget(le, 0, 2, Qt::AlignHCenter);
   layout->addWidget(new QLabel(text1), 0, 3, Qt::AlignCenter);
   layout->addWidget(le1, 0, 4, Qt::AlignHCenter);

   QWidget *widget = new QWidget;
   widget->setLayout(layout);
   //connect(box, SIGNAL(valueChanged(int)),this, SLOT(slotSpinValue(int )));
   //connect(le, SIGNAL(textChanged ( const QString)), windowMapper, SLOT(map()));
   //windowMapper->setMapping(le, ty);
   //connect(tb,  SIGNAL(triggered(QAction * action )), windowMapper, SLOT(map()));
   connect(tb,  SIGNAL(clicked()), windowMapper, SLOT(map()));
   windowMapper->setMapping(tb, ty);
   return widget;
}
QWidget* dtMainWin::createEditWidget(const QString& text, const QString& tip, int ty, QString v, QLineEdit *& edit)
{
   QString str;
   str = tip;
   QLineEdit *le = new QLineEdit;
   le->setMaximumWidth(LINEEDIT_WIDTH);
   le->setText(v);
   edit = le;
   QGridLayout *layout = new QGridLayout;
   QToolButton *tb = new QToolButton();
   tb->setText(text);
   tb->setToolTip(str);

   layout->addWidget(tb, 0, 0, Qt::AlignCenter);
   layout->addWidget(le, 0, 1, Qt::AlignHCenter);
   QWidget *widget = new QWidget;
   widget->setLayout(layout);
   //connect(box, SIGNAL(valueChanged(int)),this, SLOT(slotSpinValue(int )));
   //connect(le, SIGNAL(textChanged ( const QString)), windowMapper, SLOT(map()));
   //windowMapper->setMapping(le, ty);
   //connect(tb,  SIGNAL(triggered(QAction * action )), windowMapper, SLOT(map()));
   connect(tb,  SIGNAL(clicked()), windowMapper, SLOT(map()));
   windowMapper->setMapping(tb, ty);
   return widget;
}
QWidget* dtMainWin::createSpinWidget(const QString& text, const QString& tip, int ty, int v, int min, int max, int step)
{
   QString str;
   str = tip;
   QSpinBox *box = new QSpinBox;
   box->setValue(v);
   box->setMinimum(min);
   box->setMaximum(max);
   box->setSingleStep(step);
   box->setToolTip(str);
   QGridLayout *layout = new QGridLayout;

   layout->addWidget(new QLabel(text), 0, 0, Qt::AlignCenter);
   layout->addWidget(box, 0, 1, Qt::AlignHCenter);
   QWidget *widget = new QWidget;
   widget->setLayout(layout);
   //connect(box, SIGNAL(valueChanged(int)),this, SLOT(slotSpinValue(int )));
   connect(box, SIGNAL(valueChanged(int)), windowMapper, SLOT(map()));
   windowMapper->setMapping(box, ty);

   return widget;
}
QWidget* dtMainWin::createSliderWidget(const QString& text, const QString& tip, int ty, int v, int min, int max, int step)
{
//   qDebug() << "slider";
   QString str;
   str = tip;
   QSlider *box = new QSlider;
   box->setValue(v);
   box->setMinimum(min);
   box->setMaximum(max);
   box->setSingleStep(step);
   box->setToolTip(str);
   box->setOrientation(Qt::Horizontal);
   QGridLayout *layout = new QGridLayout;
//qDebug() << "slider";
   layout->addWidget(new QLabel(text), 0, 0, Qt::AlignCenter);
   layout->addWidget(box, 0, 1, Qt::AlignHCenter);
   QWidget *widget = new QWidget;
   widget->setLayout(layout);
//   qDebug() << "slider";
//connect(box, SIGNAL(valueChanged(int)),this, SLOT(slotSpinValue(int )));
   connect(box, SIGNAL(valueChanged(int)), windowMapper, SLOT(map()));
   windowMapper->setMapping(box, ty);
//qDebug() << "slider" <<widget;
   return widget;
}
void dtMainWin::createStatusBar()
{
   statusBar()->showMessage(tr("Ready"));
   //qDebug() << "create StatusBar";
}
void dtMainWin::setStatus(QString st)
{
   statusBar()->showMessage(st);
   //qDebug() << "create StatusBar";
}

void dtMainWin::slotOpenFile()
{

   QPixmap shotIcon;
   QString dir, str, filter, title, s;
   title = "Open File;";
   dir = "";
   filter = QString("Segy files (*.sgy);; All files (*.*)");
   //dir = data->m_strDir;

   s = QFileDialog::getOpenFileName(this, title, dir, filter);
   if (s.isEmpty()) return;


   //openFile(s);
   return;
}

void dtMainWin::slotHelp()
{
   QString cmd, str;
   //cmd = SHOWPDF;
   cmd = SHOW_PDF + DOC->pathConfig() + MARK_PATH + APP_DOC;
   //cmd = "ls";
   qDebug() << "cmd=" << cmd;
   hrun.start(cmd);
}
void dtMainWin::slotAbout()
{
   QString title, str, str1;
   title = ORG_NAME;
   str1 = __DATE__;
   str = QString("App name : ") + QString(APP_NAME) + "\n" +
      QString("App version : ") + QString(APP_VERSION) + "\n" +
      QString("App Build Date : ") + str1;
   QMessageBox::about(this, title, str);
}

void dtMainWin::slotTapeConfig()
{
//moveData(MOVE_LAST);
   QStringList slist;
   QString str;
   int i;
   slist = DOC->getTapeConfig();
   qDebug() << " get tape Config = " << slist;

   dlgE->setTitle("Tape Config");
   dlgE->resize(TAPE_SIZE);

   slist.insert(0, TAPE_COMM);
   dlgE->setList(slist);
   i = dlgE->exec();
   if (i == 1)
   {
      qDebug() << "yes ";
      slist.clear();
      slist = dlgE->getList();
      //slist.insert(0,TAPE_COMM);
      qDebug() << "list = " << slist;
      DOC->saveTapeConfig(slist);

      for (i = slist.size() - 1; i >= 0; i--)
      {
         str = slist[i];
         if (isComm(str))
         {
            slist.removeAt(i);
         }
      }
      inputV->setTapes(slist);
      outputV->setTapes(slist);
   }
   else qDebug() << "No ";


   qDebug() << "tape";
}
void dtMainWin::slotParaConfig()
{
   qDebug() << "para";
   paramD->exec();
   paramD->getParam();

//moveData(MOVE_LAST);
}

void dtMainWin::slotLogView(QTreeWidgetItem *item, int col)
{
   qDebug() << "slotLogView";
   //moveData(MOVE_LAST);
   QString str, jname;
   int i;
   jname = item->text(JOB_NAME);

   str = "LOG -" + jname;
   dlgE->setTitle(str);
   dlgE->resize(LOG_SIZE);

   str = getFileText(DOC->fileJobLog(jname));
   dlgE->setText(str);
   i = dlgE->exec();
   //qDebug() << "log";
//moveData(MOVE_LAST);
}
void dtMainWin::slotLicConfig()
{
   qDebug() << "lic";
//moveData(MOVE_LAST);
}
 
void dtMainWin::slotInputBT()
{
 
     deviceBT(inputV);
}
void dtMainWin::slotOutputBT()
{

     deviceBT(outputV);
}
void dtMainWin::deviceClose()
{
   if(ana.dio.isOpen())
        ana.dio.close();

   inputV->setBT(0);
   outputV->setBT(0);
}
void dtMainWin::deviceBT(inputView *v)
{
   int iret;
   QString st;
   st = "OK";

   deviceClose();

   ana.dev = v->getDev();

 
   iret = ana.dio.openDev(&ana.dev, 0);
   if (iret != OPENFILE_OK)
   {
      
      st = "open dev error dev = " + ana.dev.name ;
      qDebug() << "open dev return = " << st;
   }
   else
   {
       v->setBT(1);
   }
   setStatus(st);
}
void dtMainWin::slotParam(int i)
{
   QString x, y;
   //bool b;
   // int num, j;

   if (i == PARAM_AMP_AGC)
   {
      //qDebug() << "agc idx = " << i << agcEdit;
      QLineEdit *b = agcEdit;
      //qDebug() << " gagc text = " << b->text();
   }
}

void dtMainWin::setTitle()
{

   QString str;
   str = "";
   str = str + APP_NAME + "-" + APP_VERSION + "-" + __DATE__; // + "-";
                                                              //str = str + DOC->m_dataName;
   setWindowTitle(str);

}
void dtMainWin::closeEvent(QCloseEvent *event)
{
   /*
       mdiArea->closeAllSubWindows();
    if (mdiArea->currentSubWindow()) {
        event->ignore();
    } else {
        writeSettings();
        event->accept();
    }
    */
   writeSettings();
   //qDebug() << "1111111";
   QString str;
   str = "DataTool exit";
   DOC->logS->tline(str);
   DOC->logS->close();
}
void dtMainWin::slotJobStart()
{
   DEV in, out;
   QString jbname;
   in = inputV->getDev();
   out = outputV->getDev();


   *DOC->devIn = in;
   *DOC->devOut = out;
// job:
   jbname = DOC->jobname();
   DOC->_jobname = jbname;

// format check
   copyITF pcp;
   int b;
   b = DOC->checkDev(); //in: is exist,out if exist ask;
   if (b != OPEN_OK)
   {
      msgOut(pcp.cpErr[b]);
      return;
   }
   b = startConform(); // display and ask:
   if (!b)
   {
      msgOut("Copy Canceled !!!");
      return;
   }
   qDebug() << "conform";
   deviceClose();// close the device if opened for anaTape;
//log: file open:
   DOC->logJ->setName(DOC->fileJobLog(jbname));
// begin:
   qDebug() << "jbname = " << jbname;
   DOC->logApp();
   DOC->logJob();
   DOC->logDev();
    qDebug() << "logDev " ;
   DOC->logInput();
    qDebug() << "logInput" ;
   DOC->logOutput();
   qDebug() << "logOut" ;
   DOC->logCMD();
   qDebug() << "logCMD" ;
   runJob();

}
bool dtMainWin::startConform()
{
   QString msg, title, str;
   int i, sz;
   //return 1;
#if 0
   qDebug() << "in.n,r=" << in.name << in.reel;
   qDebug() << "out.n,r=" << out.name << out.reel;
   qDebug() << "in.n,r=" << DOC->devIn->name << DOC->devIn->reel;
   qDebug() << "out.n,r=" << DOC->devOut->name << DOC->devOut->reel;
#endif
   title = " JobMessages:";

   str = DOC->getDevInStr();
   msg += str;
   str = DOC->getDevOutStr();
   msg += str;
   str = DOC->getCopyParamStr();
   msg += str;

   str = "=====================\n ";
   msg += str;
   str = "Please conform?\n ";
   msg += str;

   return askDlg(title, msg);
}
void dtMainWin::runJob()
{
   int i;
   QString str;
   qDebug() <<  "runjob====";
   str = QString("Job Start = ") +  DOC->_jobname;
   msgOut(str);

   if (pCopy != NULL) delete pCopy;
   pCopy = new tpimgCopy();
   connect(pCopy, SIGNAL(sigFileEnd(int)), this, SLOT(slotFileEnd(int)));
//open Copy:
   i = pCopy->openCopy(*(DOC->devIn), *(DOC->devOut));
   if (i != OPEN_OK)
   {
      str   = pCopy->cpErr[i];
      qDebug() << " openCopy err = " << str;
      errDlg(str);
      return;
   }
   i = fromReel();
   if (i != 0) 
   {
       DOC->logFrom(i);
       str = "cannot found append position";
       errDlg(str);
       return;
   }
   else
   {
       DOC->logFrom(i);
   }

   i = appendReel();
   if (i != 0) 
   {
       DOC->logAppend(i);
       str = "cannot found append position";
       errDlg(str);
       return;
   }
   else
   {
       DOC->logAppend(i);
   }
   DOC->sumStart(); //clear the 4 sums
                    //WOP->btCMD.start();
//jobview:
   jobV->jobStart(DOC->_jobname); // create items
// tool buttons enable:
   WOP->btCMD.start(); // enable the buttons in toolbar
   qDebug() << "setCopy =" << pCopy << tCopy;
// startCopy:
   tCopy->setCopy(pCopy); // set copy for thread;
   qDebug() << "runFile 0";
   runFile();
}
void dtMainWin::runFile()
{
// start next file

   DOC->sumFile->start();
   DOC->sumFile->setBytes(DOC->sumOut->getBytes()); // get bytes of the file begin;
   DOC->sumFile->setFiles(DOC->sumOut->size()); // get record of file begin
// run thread;
   runThread();
   //qDebug() << " is runing0 " << tCopy->isRunning();
   //tCopy->start();
   //qDebug() << " is runing " << tCopy->isRunning();
}
void dtMainWin::runThread() // begin sum and run thread
{
// run thread;
//qDebug() << " is runing0 " << tCopy->isRunning();
// wait
   if (tCopy->isRunning()) tCopy->wait();

   tCopy->start();
   //qDebug() << " is runing " << tCopy->isRunning();
}
void dtMainWin::slotFileEnd(int sta)
{
   qDebug() << "slotFileEnd st= " << sta << pCopy->cpErr[sta] << DOC->sumFile->size();
   int i;
   //sleep(1);
   switch (sta)
   {
   case COPY_EOF:
      fileEof(); // file sumary
      runFile(); //continue
      break;
   case COPY_EOT:
   case COPY_EOF2:
 #if 0
      if (DOC->devIn->type == DEV_DISK)
      {
         fileEof();
         DOC->_iEOT = 0;
      }
      else DOC->_iEOT = 1;
#endif
      //endJob(0);
      DOC->logReel();
 
// still more reel to input:
      i = endReel(sta); 

      if(i < 0)  endJob(-1);
      else if (i ==0)  endJob(0);
      else if (i > 0) runFile();

      break;
   case COPY_STOP_ERR:
      qDebug() << "Job err = " << pCopy->cpErr[sta];
      endJob(sta);
      break;
   case COPY_PAUSE_ERR:
      //endJob(); do nothing
      break;
   default:
      qDebug() << "Job err = " << pCopy->cpErr[sta];
      endJob(sta);
      break;
   }
}
void dtMainWin::fileEof()
{
   DOC->sumFile->elapsed(); // size() ids the files
   DOC->sumFile->setFiles(DOC->sumOut->size() - DOC->sumFile->getFiles()); // record of this file
   DOC->sumFile->setBytes(DOC->sumOut->getBytes() - DOC->sumFile->getBytes()); // bytes of this file
   DOC->logF();
   jobV->slotJobStat();
   // qDebug() << "end of dtMainWin::fileEof()";
   //sleep(1);

}
int dtMainWin::endReel(int sta)
{
   int i;

   QString str, str1;

 
// end of job:
   //if (DOC->getDevInFileList().size() <= 1)   // this is not proper,test failed:
   if (pCopy->tpIn.dev.type == DEV_TAPE) 
   {
       // not a multyfile input:
      return endReelTape(sta);
      //return 0;
   }
// multiple file input:
// log reel:
   
// if all input down:
   if (DOC->sumReel->size() + 1 >= DOC->getDevInFileList().size()) // not closeed so +1
   {
      //DOC->sumReel->elapsed(); in copyclose()
      //endJob(0);
      return 0;//endof file 0
   }
    qDebug() << "reelEnd  " ;
// close in and open:
   if (pCopy != NULL) // new input reel
   {
      pCopy->closeIn();
      DOC->sumReel->elapsed();
      //  log mark:
      DOC->devIn->name = DOC->getDevInFileList()[DOC->sumReel->size()];
      //qDebug() << "reelEnd ="   <<pCopy;
      //str = pCopy->cpErr[ie];
     
      i = pCopy->openIn(*DOC->devIn);
      if (i != OPEN_OK) return i;
      DOC->sumReel->start();
   }
   //runFile();// go next file;
   return 1;//runFile >0;
}
// multi reel tape input
int dtMainWin::endReelTape(int sta)
{
   int i,sz;
   QString str, str1;
   sz = DOC->getParamCopyReels();

   qDebug() << "endReelTape ;Copy reels,current reel = " << sz <<DOC->sumReel->size();
// if EOT: must be a error,even sz == DOC->sumReel->size()
   if (sta == COPY_EOT) 
   {
       str = "No more reel data in input device";
       DOC->logErr(str);
       return -1;
   }
// end of input tape( int multi reel tape or TPIMG) down:
  // all thing 
 
   if (DOC->sumReel->size() +1 >= sz) 
   {
       return 0;
   }
//  
   qDebug() << "reelMore  " ;
// close in and open:
   if (pCopy != NULL)
   {
      DOC->sumReel->elapsed();
      DOC->sumReel->start();   
   }
   //DOC->logReel(); 
   //open new file  
   i = newOutputReel();
   if (i <0) 
   {
       return i;
   }
   // log new file
   DOC->logNewReel();
   // go
   //runFile(); // go next file;
   return 1;
}
void dtMainWin::endJob(int ie)
{
   QString str, str1;
   DOC->logEnd();
   qDebug() << "jobEnd =" << ie << pCopy;
   str = pCopy->cpErr[ie];
   qDebug() << "jobEnd = " << str;

   if (pCopy != NULL)
   {
      pCopy->closeCopy();
      delete pCopy;
      pCopy = NULL;
   }

   if (ie == 0)  DOC->logJobEnd("OK");
   else DOC->logJobEnd("ERR");

   DOC->logSum();
   DOC->logClose();
   //DOC->sumEnd();// sumStart() is enough;
   WOP->btCMD.clear();
   str = QString("Job End = ") + QString("%1 , ").arg(ie) +  DOC->_jobname;
   msgOut(str);
   jobV->jobEnd(ie);


}

void dtMainWin::slotJobPause()
{
   QString str;
   if (WOP->btCMD.isPause()) // status is pause, so continue to copy file
   {
      qDebug() << "job conninue ";
      str = QString("Job continued = ") +  DOC->_jobname;
      msgOut(str);
      WOP->btCMD.goon();
      DOC->logGoon();
      jobV->jobSta("Continued");
      runThread();
   }
   else // is runing so pause;
   {
      qDebug() << "job pause ";
      str = QString("Job Paused = ") +  DOC->_jobname;
      msgOut(str);

      WOP->btCMD.pause();
      DOC->logPause();
      jobV->jobSta("Paused");
   }
}
void dtMainWin::slotJobStop()
{
   QString str;
   qDebug() << "job stop ";
   str = QString("Job Stoped = ") +  DOC->_jobname;
   msgOut(str);
   WOP->btCMD.stop();
   DOC->logStop();

}
int dtMainWin::newOutputReel()// copy more reel ,create next file to output:
{
    QString name,nname,str;
    int ic,i;
    DEV dev;
 
    dev = *DOC->devOut; 
    if (dev.type == DEV_TAPE) return 0;
    if (TPIMG_M_REEL) return 0;

    ic = DOC->sumReel->size(); 
    name = dev.name;
    nname =  DOC->getNextName(name,ic);
    
    i = pCopy->closeOut();
    if (i != 0) return -1; 
    dev.name = nname;
    i = pCopy->openOut(dev);
    if (i != OPEN_OK) return -1;
    return 0;
}
int dtMainWin::fromReel()
{
    int from;
    from = DOC->getParamCopyFrom() -1 ;
    return skipReel(&pCopy->tpIn,from);
}
int dtMainWin::appendReel()
{
    int app;
    app = DOC->getParamCopyAppend();
    return skipReel(&pCopy->tpOut,app);
    #if 0
    int app,ic,ie,i;
    int len;
    char buf[TAPE_BLOCK];
    len = 100;// tape will change to TAPE_BLOCK
    app = DOC->getParamCopyAppend();
    if (app <= 0) return 0;
//
    if (DOC->devOut->type != DEV_TAPE) return 0;// not tape device;
// position
    ic = 0;
    ie = 0;
    while (ic == app) 
    {
        // skip eof:
        i = pCopy->tpOut.fileForword();
        if (i != 0) 
        {
            ie = -1;
            break;
        }
        //read a record :
        i = pCopy->tpOut.read(buf,len);
        if (i <0 ) 
        {
            ie = -1;
            return;
        }
        else if (i == 0) 
        {// if eof: a reel end (2EOFS)
            ic++;
        }
        //i >0  ,not a 2EOFS continue to find;
    }
    return ie; 
    #endif
}
int dtMainWin::skipReel(dataIO *io,int n)
{
    int app,ic,ie,i;
    int len;
    unsigned char buf[TAPE_BLOCK];
    DEV dev;
    dev = io->dev;

    app = n;
    len = 100;// tape will change to TAPE_BLOCK
    qDebug() << "skipReels n=" << app;
    if (app <= 0) return 0;
//
    if (dev.type == DEV_DISK) return 0;// not tape device;
// position
    ic = 0;
    ie = 0;
    while (ic != app) 
    {
        // skip eof:
        i = io->fileForword();
        qDebug() << "file forword = " << i;
        if (i != 0) 
        {
            ie = -1;
            break;
        }
        //read a record :
        i = io->read(buf,len);
        qDebug() << "file read = " << i;
        if (i <0 ) 
        {
            ie = -1;
            break;
        }
        else if (i == 0) 
        {// if eof: a reel end (2EOFS)
            ic++;
        }
        //i >0  ,not a 2EOFS continue to find;
    }
    return ie; 
}
void dtMainWin::addAnaTape()
{
    locationToolBar  = addToolBar(tr("Location"));
    dumpToolBar  = addToolBar(tr("Dump"));

    anaMenu = menuBar()->addMenu(tr("&Analisys"));
    ana.createActions();
    ana.createLocationToolBar(locationToolBar);
    ana.createDumpToolBar(dumpToolBar);
    ana.createMenus(anaMenu);


}

