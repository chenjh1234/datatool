#ifndef PARAM_DLG_H
#define PARAM_DLG_H
#include <QDialog>
#include <QString>
#include <QDebug>
#include "ui_paramDlg.h"
#include "ui_deviceParam.h"
#include "ui_copyParam.h"
#define DEVICE_DISK "DISKFILE"
#define DEVICE_TPIMG "TPIMG"
#define DEVICE_REEL "reel0000"

class paramDlg :public QDialog
{
    Q_OBJECT

public:
    paramDlg(QWidget *p);
    //paramView(QWidget *p,int idd);
    ~paramDlg();
    void init();

    void getParam();
public   slots:
 //   void slotFileOpen();
 //   void slotComBox(const QString);
    
protected:
private:
    QGridLayout *lyout;
    QWidget *inputW,*outputW,*copyW;
 
    //Ui::FormDev ui;
    Ui::DialogParam uiDlg;
    Ui::copyParam uiCopy;
    Ui::deviceParam uiDevIn,uiDevOut;
};
#endif
