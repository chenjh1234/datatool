#include "inputview.h"
#include "dtapp.h"
inputView::inputView(QWidget *p,int id) : QWidget(p)
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

// test tapelist:
   QStringList slist;
   //slist <<"/dev/st0 3480 500" << "/dev/st1 8mm 500";
   //slist <<"/dev/st0 3480 500";
    
   slist = DOC->getTapeConfig();
   setTapes(slist); 
 
   ui.lineEditDisk->setText(DEVICE_REEL);
// connect File:
   connect(ui.comboBoxTape, SIGNAL(	currentIndexChanged(const QString)), this, SLOT(slotComBox(const QString)));
   connect(ui.pushButtonFile, SIGNAL(clicked()), this, SLOT(slotFileOpen()));

}
void inputView::slotComBox(const QString str)
{
 
    
    if (ui.pushButtonCheck->text() == QString("Input")) 
    {
        //if (str == DEVICE_DISK || str == DEVICE_TPIMG) 
        if ( str == DEVICE_TPIMG) 
        {
            //ui.lineEditDisk->setText(DEVICE_REEL);
            //qDebug() <<"bSetTape =" <<_bSetTape << ui.pushButtonCheck->text();
           // if (!_bSetTape)
            //qDebug() << 
            if(ui.comboBoxTape->count() > 1)
                slotFileOpen(); 
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
 
void inputView::slotFileOpen()
{
    QString filename,dir,filter;
    dir = lastDir;
    filter =  tr("SegFiles (*.sgy *.sgd *.TPIMG);; Allfiles(*.*)");
    if (m_id == 1)
    {
        filename = QFileDialog::getSaveFileName(this,
                   tr("Open File"), dir, filter);
    }
    else
    {
        filename = QFileDialog::getOpenFileName(this,
                   tr("Open File"), dir, filter);
    }
    
    ui.lineEditDisk->setText(filename);
    ui.lineEditDisk->setToolTip(filename);
}
DEV inputView::getDev()
{
    DEV d;
    QString str,ty;
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
        if (slist.size() > 1)  
            d.id = slist[1]; 
        if (slist.size() > 2)
            d.size = atoi(slist[2].Q2CH);
    }
    return d;
}
 
