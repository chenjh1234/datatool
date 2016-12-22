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
bool optionDlg::isCopyPrompt()
{
      return ui.checkBoxCopyPrompt->isChecked();
}
bool optionDlg::isCopyToolbar()
{
      return  ui.checkBoxCopyBar->isChecked();
}
int optionDlg::getTapeBlock()
{
    int i;
    QString str;
    str = ui.lineEditTapeBlock->text();
    i = str.toInt();
    return i;
}
void optionDlg::setTapeBlock(int len)
{
    int i;
    QString str;
    str.setNum(len);
    qDebug() << "option in setTapeBlock = " <<len << str;
    ui.lineEditTapeBlock->setText(str);
}
void optionDlg::setCopyToolbar(bool b)
{
    ui.checkBoxCopyBar->setChecked(b);
}
void optionDlg::setCopyPrompt(bool b)
{
    ui.checkBoxCopyPrompt->setChecked(b);
}
    
 
