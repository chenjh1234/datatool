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

   
   uiDevIn.setupUi(inputW);
   uiDevOut.setupUi(outputW);
   uiCopy.setupUi(copyW);
   uiDevIn.groupBoxDev->setTitle("Input Device:");
   uiDevOut.groupBoxDev->setTitle("output Device:");
 
// connect File:
   //connect(ui.comboBoxTape, SIGNAL(	currentIndexChanged(const QString)), this, SLOT(slotComBox(const QString)));
  // connect(ui.pushButtonFile, SIGNAL(clicked()), this, SLOT(slotFileOpen()));

}
void paramDlg::getParam()
{
// input start:
    if(uiDevIn.radioButtonRewind->isChecked())
        DOC->pStartIn = PARAM_REWIND;
    else
        DOC->pStartIn = PARAM_NOT_REWIND;

// input end:
    if(uiDevIn.radioButtonRewindUnloadEnd->isChecked())
        DOC->pEndIn = PARAM_REWIND_UNLOAD;
    else if (uiDevIn.radioButtonRewindEnd->isChecked())  
        DOC->pEndIn = PARAM_REWIND; 
    else
        DOC->pEndIn = PARAM_NOT_REWIND; 

// output start:
    if(uiDevOut.radioButtonRewind->isChecked())
        DOC->pStartOut = PARAM_REWIND;
    else
        DOC->pStartOut = PARAM_NOT_REWIND;

// output end:
    if(uiDevOut.radioButtonRewindUnloadEnd->isChecked())
        DOC->pEndOut = PARAM_REWIND_UNLOAD;
    else if (uiDevOut.radioButtonRewindEnd->isChecked())  
        DOC->pEndOut = PARAM_REWIND; 
    else
        DOC->pEndOut = PARAM_NOT_REWIND; 
// copy:
    QString str;
    str = uiCopy.lineEdit->text();
    DOC->pCopy  = str.toInt();

    qDebug() << "devIn Param = "<< DOC->pStartIn << DOC->pEndIn ;
    qDebug() << "devOut Param = "<< DOC->pStartOut << DOC->pEndOut ;
    qDebug() << "copy Param = "<< DOC->pCopy;


}
 
