#include "editdlg.h"
editDlg::editDlg(QWidget *p):QDialog(p)
{
    init();
}
 
editDlg::~editDlg()
{
}
void editDlg::init()
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
void editDlg::setText(QString in)
{
    ui.textEdit->setText(in);
}
void editDlg::setList(QStringList in)
{
    QString str;
    int i;
     ui.textEdit->clear();
    for (i =0; i< in.size(); i++)
    {
        str = in[i]; 
        ui.textEdit->append(str);
    }
   
}
QString editDlg::getText()
{
    return ui.textEdit->toPlainText();
}
QStringList editDlg::getList()
{
    QString str;
    str = getText();
    return str.split("\n");
}
void editDlg::setTitle(QString t)
{
    setWindowTitle(t);
}
void editDlg::setReadOnly()
{
    ui.textEdit->setReadOnly(true);
}
 
