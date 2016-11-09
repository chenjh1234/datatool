
#include "fileListDlg.h"
#include "dtapp.h"
#include <QDateTime>
#include <QTreeWidgetItem>

fileListDlg::fileListDlg(QWidget *p):QDialog(p)
{
    init();
}
 
fileListDlg::~fileListDlg()
{
}
void fileListDlg::init()
{
   ui.setupUi(this);
   lastDir = "";
   connect(ui.pushButtonAdd, SIGNAL(clicked()), this, SLOT(slotAdd()));
   connect(ui.pushButtonRemove, SIGNAL(clicked()), this, SLOT(slotRemove()));
   connect(ui.pushButtonClear, SIGNAL(clicked()), this, SLOT(slotClear()));
   connect(ui.pushButtonUp, SIGNAL(clicked()), this, SLOT(slotUp()));
   connect(ui.pushButtonDown, SIGNAL(clicked()), this, SLOT(slotDown()));
   connect(ui.pushButtonUnselect, SIGNAL(clicked()), this, SLOT(slotUnselect()));
   QStringList slist;
   slist << "filename" <<"size" << "last modify";
   ui.treeWidget->setHeaderLabels(slist);
    // header()->setResizeMode(QHeaderView::ResizeToContents );
   ui.treeWidget->resizeColumnToContents(FILE_NAME);
   ui.treeWidget->setColumnWidth(FILE_NAME,300);
   ui.treeWidget->setSortingEnabled(true);
   ui.treeWidget->setSelectionMode(QAbstractItemView::MultiSelection);
}
 
void fileListDlg::addItem(QStringList it)
{
    #if 1
     QTreeWidgetItem *item;
     item = new QTreeWidgetItem(ui.treeWidget);
     item->setText(FILE_NAME,it[0]);
     item->setText(FILE_SIZE,it[1]);
     item->setText(FILE_LASTMODIFY,it[2]);
     ui.treeWidget->insertTopLevelItem(0,item);
    #endif
}
QStringList fileListDlg::getList()
{
    int i;
    QString str,strs;
    QStringList slist;
    qDebug() << "size of items = " << ui.treeWidget->topLevelItemCount();
    int sz;
    sz = ui.treeWidget->topLevelItemCount();
    slist.clear();
    listZF.clear();

    for (i = 0; i< sz ;i++) 
    {
        str = ui.treeWidget->topLevelItem(i)->text(FILE_NAME);
        slist << str;
        strs = ui.treeWidget->topLevelItem(i)->text(FILE_SIZE);
        if (strs == QString("0")) 
        {
            listZF << str;
        }
    }
    return slist; 
}

void fileListDlg::slotAdd()
{
    int i;
    QString  dir,filter,str,line ;
    QString name,dt;
    int sz;
    QStringList fList,sList;
    dir = lastDir;
    filter =  tr("SegFiles (*.sgy *.sgd *.TPIMG);; Allfiles(*.*)");
    fList = QFileDialog::getOpenFileNames(this,
                   tr("Open Files"), dir, filter);
    if (fList.size() <= 0) return;
    QFileInfo fi(fList[0]);
    lastDir = fi.absolutePath();
    for (i = 0; i < fList.size() ; i++) 
    {
        fi.setFile(fList[i]);
        name = fi.absoluteFilePath();
        sz = fi.size();///1024;//in K
        dt= fi.lastModified().toString();
        sList.clear();
        sList << name << QString("%1").arg(sz) << dt;
        //qDebug()<<"list = " << name << QString("%1").arg(sz) << sz << dt;
        addItem(sList);
    }
}

void fileListDlg::moveSelectedItem(int wh)
{
    int sz,ssz ,i,idx;
    QList<QTreeWidgetItem *> listItem;
    QTreeWidgetItem *item, *item1;
    listItem = ui.treeWidget->selectedItems();
    if (wh== MOVE_REMOVE) 
    {
        i = WIN->askDlg("Remove Selected Items??");
        qDebug() << "ask =" << i;
        if( i == 0) return;
    }
    ui.treeWidget->setSortingEnabled(false); 
   
    ssz = listItem.size();
    sz = ui.treeWidget->topLevelItemCount();
    qDebug() << "selections = " << ssz << sz;
    for (i = 0; i <ssz;i++)
    {
        item = listItem[i];
        idx = 	ui.treeWidget->indexOfTopLevelItem(item);
        qDebug() << "idx,where = " << idx << wh;
        if (wh == MOVE_UP)  
        if (idx > 0) 
        {       
            ui.treeWidget->takeTopLevelItem(idx);
            ui.treeWidget->insertTopLevelItem(idx -1,item);
            //ui.treeWidget->setCurrentItem(item);
            item->setSelected(true);
        }
        if (wh == MOVE_DOWN)  
        if (idx < sz-1) 
        {
            item1 = ui.treeWidget->topLevelItem(idx+1);
            qDebug() << "idx  = " << item->text(0);
            qDebug() << "idx + 1 = " << item1->text(0);
             
            ui.treeWidget->takeTopLevelItem(idx+1);
            ui.treeWidget->insertTopLevelItem(idx ,item1);
            if (item1->isSelected())  
                 item1->setSelected(true);
            //ui.treeWidget->setCurrentItem(item);
        }
        if (wh == MOVE_REMOVE)                      
            ui.treeWidget->takeTopLevelItem(idx);
             
    }
}
void fileListDlg::slotRemove()
{
    moveSelectedItem(MOVE_REMOVE);
}
void fileListDlg::slotUp()
{
    moveSelectedItem(MOVE_UP);

}
void fileListDlg::slotDown()
{
    moveSelectedItem(MOVE_DOWN);

}
void fileListDlg::slotClear()
{
    if(!WIN->askDlg("Remove all The Items??")) return;
    ui.treeWidget->clear();

}
void fileListDlg::slotUnselect()
{
    ui.treeWidget->setSortingEnabled(true);
    ui.treeWidget->clearSelection();
}
