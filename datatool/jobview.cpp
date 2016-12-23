#include "jobview.h"
#include "dtapp.h"
jobView::jobView(QWidget *p):QTreeWidget(p)
{
    init();

}
jobView::~jobView()
{
    saveList();
}
void jobView::init()
{
    QStringList slist;
    slist << "jobname " <<"status";
    setHeaderLabels(slist);
    // header()->setResizeMode(QHeaderView::ResizeToContents );
     resizeColumnToContents(JOB_NAME);
     setColumnWidth(JOB_NAME,200);
     //setSortingEnabled(true);
    //QTreeWidgetItem * hd =	headerItem();
    //hd->setSizeHint(JOB_NAME,QSize(200,5));
     loadJob();
}
void jobView::jobAdd(QString j,QString st)
{
    int i;
    i = 0;
    QTreeWidgetItem *item;
    item = new QTreeWidgetItem(0);
    _job = item;
    item->setText(JOB_NAME,j);
    item->setText(JOB_STAT,st);
    //addTopLevelItem( item);
    insertTopLevelItem(i,item);
    qDebug() << " index of item = " << indexOfTopLevelItem(item);
    
}
void jobView::jobStart(QString j)
{
    QString st;
    st = "Running";
     jobAdd(j,st);
     
}
void jobView::slotJobStat()
{
    QString str;
    str = QString("%1").arg(DOC->sumFile->size());
    _job->setText(JOB_STAT,str);
    _job->setToolTip(JOB_STAT,str);
}
void jobView::jobSta(QString s)
{
    QString str;
    str = s;
    _job->setText(JOB_STAT,str);
    _job->setToolTip(JOB_STAT,str);
}
void jobView::jobEnd(int id)
{
    if (id == 0)
    {
        _job->setText(JOB_STAT,"OK");
    }
    else
    {
        _job->setForeground(JOB_STAT, QBrush(Qt::red));
        _job->setText(JOB_STAT,"ERR");
    }
    addList(id);
}
void jobView::addList(int id)
{
    QString str;
    QStringList slist;
    if (id == 0) str = "OK";
    else str = "ERR";
    slist << _job->text(0) << str;
    listJob << slist;
}
void jobView::saveList()
{
    int i;
    QString str,file;
    QStringList slist;
    file = DOC->fileJobMsg();

    for (i = 0; i < listJob.size(); i++) 
    {
        str = listJob[i][0] + " " +  listJob[i][1];
        slist << str;
    }
    i = appendListToFile(file,slist);
    qDebug() << "save jobmsg = " << i << slist.size() <<file <<listJob.size();
}
void jobView::loadJob()
{
    int i,is,ie;
    QString str,file;
    QStringList slist,slist1;
    file = DOC->fileJobMsg();
    slist = getListFromFile(file);
 
    ie = slist.size()-1;
    is = slist.size()-JOBMSG_LEN;
    if (is <0 )   is = 0;

        for (i = is; i <=ie ; i++) 
        {
            str = slist[i];
            slist1 = str.split(" ");
            jobAdd(slist1[0],slist1[1]);
        }
  
    qDebug() << "load JOb ";
}
