#include "inputview.h"
#include "dtapp.h"
#include <QPalette>
inputView::inputView(QWidget *p, int id) : QWidget(p)
{
   m_id = id;
   init();
}
inputView::inputView(QWidget *p) : QWidget(p)
{
   m_id = 0;
   init();
}
inputView::~inputView()
{

}
void inputView::init()
{
   ui.setupUi(this);
   lastDir = "";
   fDlg = new fileListDlg(this);

// test tapelist:
   QStringList slist;
   //slist <<"/dev/st0 3480 500" << "/dev/st1 8mm 500";
   //slist <<"/dev/st0 3480 500";

   slist = DOC->getTapeConfig();
   setTapes(slist);

   ui.lineEditDisk->setText(DEVICE_REEL);
// connect File:
   connect(ui.comboBoxTape, SIGNAL(currentIndexChanged(const QString)), this, SLOT(slotComBox(const QString)));
   connect(ui.pushButtonFile, SIGNAL(clicked()), this, SLOT(slotFileOpen()));
   //connect(ui.pushButtonCheck, SIGNAL(clicked()), this, SLOT(slotFileList()));

}
void inputView::slotComBox(const QString str)
{


   if (ui.pushButtonCheck->text() == QString("Input"))
   {
      //if (str == DEVICE_DISK || str == DEVICE_TPIMG)
      if (str == DEVICE_TPIMG)
      {
         //ui.lineEditDisk->setText(DEVICE_REEL);
         //qDebug() <<"bSetTape =" <<_bSetTape << ui.pushButtonCheck->text();
         // if (!_bSetTape)
         //qDebug() <<
         if (ui.comboBoxTape->count() > 1) slotFileOpen();
         //_bSetTape = false;
      }
   }
}
void inputView::setDev(QString in)
{
   ui.pushButtonCheck->setText(in);
}
void inputView::setTapes(QStringList list)
{
   //_bSetTape = true;
   ui.comboBoxTape->clear();
   if (m_id == 0)
   {
      ui.comboBoxTape->addItems(list);
      // ui.comboBoxTape->addItem(DEVICE_DISK);
      ui.comboBoxTape->addItem(DEVICE_TPIMG);
   }
   else
   {
      ui.comboBoxTape->clear();
      ui.comboBoxTape->addItem(DEVICE_TPIMG);
      // ui.comboBoxTape->addItem(DEVICE_DISK);
      ui.comboBoxTape->addItems(list);
   }
   // qDebug() <<"in setTapes bSetTape =" <<_bSetTape;
}

void inputView::slotFileList()
{
   QString filename, dir, filter, str;
   QStringList slist;
   if (m_id == 1) return; // output device do nothing
   int i;
#if 1
   i = fDlg->exec();
   qDebug() << " fileDlg return=" << i;

   if (i != 0)
   {
      slist = fDlg->getList();
      if (fDlg->listZF.size() > 0)
      {
         //qDebug() <<  "file size == 0, file=" << fDlg->listZF;
         str = fDlg->listZF.join(" ");
         str = "file size == 0 :" + str;
         WIN->errDlg(str);
      }
      //qDebug() << "files size = " << slist.size();
      //qDebug() << "files = " << slist;
      // this is default:
      str = "background-color: qlineargradient(x1: 0, y1: 0, x2: 0, y2: 1,\
                                      stop: 0 #f6f7fa, stop: 1 #dadbde";
      if (slist.size() > 1)
      {

         ui.pushButtonCheck->setStyleSheet("background-color:#993300");
         //ui.pushButtonCheck->setBackgroundRole(1);//QPalette::Background);
      }
      else ui.pushButtonCheck->setStyleSheet(str);

      DOC->setDevInFileList(slist);
   }
#endif

}

void inputView::slotFileOpen()
{
   QString filename, dir, filter;
   dir = lastDir;
   filename = "";

   filter =  tr("SegFiles (*.sgy *.sgd *.TPIMG);; Allfiles(*.*)");
   if (m_id == 1)
   {
      filename = QFileDialog::getSaveFileName(this,
                                              tr("Open File"), dir, filter);
   }
   else
   {
      // filename = QFileDialog::getOpenFileName(this,
      //           tr("Open File"), dir, filter);
      if (fDlg->files() == 0)
      {
         fDlg->setDir(dir);
         fDlg->slotAdd();

         if (fDlg->files() == 1)
         {
            filename = fDlg->getList()[0];
         }
         else if (fDlg->files() > 1)
         {
            slotFileList();
            filename = fDlg->getList()[0];
         }
      }
      else
      {
         slotFileList();
         filename = fDlg->getList()[0];
      }

   }
   QFileInfo fi(filename);
   lastDir = fi.absolutePath();
   ui.lineEditDisk->setText(filename);
   ui.lineEditDisk->setToolTip(filename);
}
DEV inputView::getDev()
{
   DEV d;
   QString str, ty;
   QStringList slist;
   d.id = "";
   d.size = 0;
   d.reel = "";

   ty = ui.comboBoxTape->currentText();
   str = ui.lineEditDisk->text();
   slist = ty.split(" ");
   d.name = slist[0];
   if (d.name == DEVICE_DISK)
   {
      d.name = str;
      d.type = DEV_DISK;

   }
   else if (d.name == DEVICE_TPIMG)
   {
      d.name = str;
      d.type = DEV_TPIMG;

   }
   else
   {
      d.type = DEV_TAPE;
      d.reel = str;
      if (slist.size() > 1)  d.id = slist[1];
      if (slist.size() > 2) d.size = atoi(slist[2].Q2CH);
   }
   return d;
}

