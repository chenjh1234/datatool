#include "optionDlg.h"
optionDlg::optionDlg(QWidget *p):QDialog(p)
{
    init();
}
 
optionDlg::~optionDlg()
{
}
void optionDlg::init()
{
   ui.setupUi(this);
#if 0
   QStringList slist;
   slist << "/dev/st0 3480 500" << "/dev/st1 8mm 500";
   if (m_id == 0)  setTapes(slist);
   else setOTapes(slist);
   ui.lineEditDisk->setText(DEVICE_REEL);
// connect File:
   connect(ui.comboBoxTape, SIGNAL(currentIndexChanged(const QString)), this, SLOT(slotComBox(const QString)));
   connect(ui.pushButtonFile, SIGNAL(clicked()), this, SLOT(slotFileOpen()));
#endif
}
void optionDlg::setText(QString in)
{
   // ui.textEdit->setText(in);
}
void optionDlg::setList(QStringList in)
{
    
}
QString optionDlg::getText()
{
    
}
QStringList optionDlg::getList()
{
     
}

void optionDlg::setReadOnly()
{
     
}
 
