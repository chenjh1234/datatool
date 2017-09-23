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
   h80W = new QWidget(this);

   lyout->addWidget(inputW, 0, 0, 1, 1);
   lyout->addWidget(outputW, 1, 0, 1, 1);
   lyout->addWidget(copyW, 2, 0, 1, 1);
   lyout->addWidget(h80W,3,0,1,1);
   lyout->addWidget(uiDlg.buttonBox,4,0,1,1);

   
   uiDevIn.setupUi(inputW);
   uiDevOut.setupUi(outputW);
   uiCopy.setupUi(copyW);
   uiH80.setupUi(h80W);
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
        DOC->setParamDevInStart(PARAM_REWIND);
    else
        DOC->setParamDevInStart(PARAM_NOT_REWIND);

// input end:
    if(uiDevIn.radioButtonRewindUnloadEnd->isChecked())
        DOC->setParamDevInEnd(PARAM_REWIND_UNLOAD);
    else if (uiDevIn.radioButtonRewindEnd->isChecked())  
        DOC->setParamDevInEnd(PARAM_REWIND); 
    else
        DOC->setParamDevInEnd(PARAM_NOT_REWIND); 

// output start:
    if(uiDevOut.radioButtonRewind->isChecked())
        DOC->setParamDevOutStart(PARAM_REWIND);
    else
        DOC->setParamDevOutStart(PARAM_NOT_REWIND);

// output end:
    if(uiDevOut.radioButtonRewindUnloadEnd->isChecked())
        DOC->setParamDevOutEnd(PARAM_REWIND_UNLOAD);
    else if (uiDevOut.radioButtonRewindEnd->isChecked())  
        DOC->setParamDevOutEnd(PARAM_REWIND); 
    else
        DOC->setParamDevOutEnd(PARAM_NOT_REWIND); 
// copy:
    QString str;
    str = uiCopy.lineEditFrom->text();
    DOC->setParamCopyFrom(str.toInt());

    str = uiCopy.lineEditCopy->text();
    DOC->setParamCopyReels(str.toInt());

    str = uiCopy.lineEditAppend->text();
    DOC->setParamCopyAppend(str.toInt());
 // h80
    bool b;
    b = uiH80.checkBoxH80->isChecked();
    DOC->setH80(b);

    b = uiH80.checkBoxRemoveTail->isChecked();
    DOC->setH80SkipTail(b);
    

    qDebug() << "devIn Param = "<< DOC->getParamDevInStart() << DOC->getParamDevInEnd() ;
    qDebug() << "devOut Param = "<< DOC->getParamDevOutStart() << DOC->getParamDevOutEnd();
    qDebug() << "copy Param = "<< DOC->getParamCopyFrom() <<DOC->getParamCopyReels() <<DOC->getParamCopyAppend();
     qDebug() << "h80 Param = "<< DOC->isH80() << DOC->isH80SkipTail();


}
 
