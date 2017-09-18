#include "nextdlg.h"
#include "dtapp.h"

nextDlg::nextDlg(QWidget *p) : QDialog(p)
{
    
   init();
}
 
nextDlg::~nextDlg()
{

}
void nextDlg::init()
{
   
   uiNext.setupUi(this);
   lyout = new QGridLayout(this);
    
 
   labelYes = new QLabel(this);
   
   labelNo = new QLabel(this);
   checkBoxH80 = new QCheckBox(this);
   labelYes->setText("    OK: Input next Reel");
   labelNo->setText( "Cancel: end of Copy");
   checkBoxH80->setText("H80: Remove the last option tail bloak");

   
   lyout->addWidget(checkBoxH80, 1, 0, 1, 1);
   lyout->addWidget(labelYes, 2, 0, 1, 1);
   lyout->addWidget(labelNo,3,0,1,1);
   lyout->addWidget(uiNext.buttonBox,4,0,1,1);

   
// connect File:
   //connect(ui.comboBoxTape, SIGNAL(	currentIndexChanged(const QString)), this, SLOT(slotComBox(const QString)));
  // connect(ui.pushButtonFile, SIGNAL(clicked()), this, SLOT(slotFileOpen()));
 
}
void nextDlg::getParam()
{
    #if 0
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

    qDebug() << "devIn Param = "<< DOC->getParamDevInStart() << DOC->getParamDevInEnd() ;
    qDebug() << "devOut Param = "<< DOC->getParamDevOutStart() << DOC->getParamDevOutEnd();
    qDebug() << "copy Param = "<< DOC->getParamCopyFrom() <<DOC->getParamCopyReels() <<DOC->getParamCopyAppend();

#endif
}
 

