#include "paramDlg.h"
#include "dtapp.h"

paramDlg::paramDlg(QWidget *p) : QDialog(p)
{
    
   init();
}
 
paramDlg::~paramDlg()
{

}
void paramDlg::init()
{
    uiDlg.setupUi(this);
   lyout = new QGridLayout(this);
   inputW = new QWidget(this);
   outputW = new QWidget(this);
   copyW = new QWidget(this);

   lyout->addWidget(inputW, 0, 0, 1, 1);
   lyout->addWidget(outputW, 1, 0, 1, 1);
   lyout->addWidget(copyW, 2, 0, 1, 1);
   lyout->addWidget(uiDlg.buttonBox,3,0,1,1);

   
   uiDev.setupUi(inputW);
   uiDev.setupUi(outputW);
   uiCopy.setupUi(copyW);
 
// connect File:
   //connect(ui.comboBoxTape, SIGNAL(	currentIndexChanged(const QString)), this, SLOT(slotComBox(const QString)));
  // connect(ui.pushButtonFile, SIGNAL(clicked()), this, SLOT(slotFileOpen()));

}
 
