#include "jobview.h"
#include "dtapp.h"
jobView::jobView(QWidget *p):QTreeWidget(p)
{
    init();

}
jobView::~jobView()
{

}
void jobView::init()
{
    QStringList slist;
    slist << "jobname " <<"status";
    setHeaderLabels(slist);
    // header()->setResizeMode(QHeaderView::ResizeToContents );
     resizeColumnToContents(JOB_NAME);
     setColumnWidth(JOB_NAME,200);
    //QTreeWidgetItem * hd =	headerItem();
    //hd->setSizeHint(JOB_NAME,QSize(200,5));
}
void jobView::jobStart(QString j)
{
     QTreeWidgetItem *item;
     item = new QTreeWidgetItem(this);
     _job = item;
     item->setText(JOB_NAME,j);
     item->setText(JOB_STAT,"runing");
     //addTopLevelItem( item);
     insertTopLevelItem(0,item);

     qDebug() << " index of item = " << indexOfTopLevelItem(item);
}
void jobView::slotJobStat()
{
    QString str;
    str = QString("%1").arg(DOC->sumAll->size());
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
}
