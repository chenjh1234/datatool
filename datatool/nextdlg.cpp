#include "nextdlg.h"
#include "dtapp.h"

nextDlg::nextDlg(QWidget *p) : QDialog(p)
{
    
   init();
}
 
nextDlg::~nextDlg()
{

}
void nextDlg::setReel()
{
    QString str;
    str = QString("%1 reels complete ").arg(DOC->sumReel->size()+1);
    labelReel->setText(str);

}
void nextDlg::init()
{
   
   uiNext.setupUi(this);
   lyout = new QGridLayout(this);
    
 
   labelReel = new QLabel(this);
   labelYes = new QLabel(this);
   
   labelNo = new QLabel(this);
   checkBoxH80 = new QCheckBox(this);
   labelYes->setText("    OK: Input next Reel");
   labelNo->setText( "Cancel: end of Copy");
   checkBoxH80->setText("H80: Remove the last option tail block??");
   checkBoxH80->setToolTip("checked: remove; unchecked: not remove");
   lyout->addWidget(checkBoxH80, 1, 0, 1, 1);
    lyout->addWidget(labelReel, 2, 0, 1, 1);
   lyout->addWidget(labelYes, 3, 0, 1, 1);
   lyout->addWidget(labelNo,4,0,1,1);
   lyout->addWidget(uiNext.buttonBox,5,0,1,1);

   
// connect File:
   //connect(ui.comboBoxTape, SIGNAL(	currentIndexChanged(const QString)), this, SLOT(slotComBox(const QString)));
  // connect(ui.pushButtonFile, SIGNAL(clicked()), this, SLOT(slotFileOpen()));
 
}
void nextDlg::getParam()
{
    bool b ;
    b = checkBoxH80->isChecked();
    DOC->setH80SkipTail(b);
    qDebug() << " is Skip tail = " <<DOC->isH80SkipTail();
}
 

