#ifndef JOB_VIEW_H
#define JOB_VIEW_H
#include <QTreeWidget>
#include <QString>
#include <QDebug>
#include <QTreeWidgetItem>

#define JOB_NAME 0
#define JOB_STAT 1

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

public   slots:
    void slotJobStat();

protected:
    QTreeWidgetItem *_job;
private:
  
};

#endif

