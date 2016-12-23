#ifndef JOB_VIEW_H
#define JOB_VIEW_H
#include <QTreeWidget>
#include <QString>
#include <QDebug>
#include <QTreeWidgetItem>
#include "comfun.h"

#define JOB_NAME 0
#define JOB_STAT 1
#define JOBMSG_LEN 10

class jobView :public QTreeWidget
{
    Q_OBJECT

public:
    jobView(QWidget *p);
    ~jobView();
    void init();
    void jobStart(QString j);
    void jobEnd(int ir);
    void jobSta(QString s);
    void jobAdd(QString s,QString st);
    void addList(int id);
    void saveList();
    void loadJob();

public   slots:
    void slotJobStat();

protected:
    QTreeWidgetItem *_job;
private:
    QList<QStringList> listJob;
  
};

#endif

