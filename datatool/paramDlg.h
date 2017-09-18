#ifndef PARAM_DLG_H
#define PARAM_DLG_H
#include <QDialog>
#include <QString>
#include <QDebug>
#include "ui_paramDlg.h"
#include "ui_deviceParam.h"
#include "ui_copyParam.h"
#include "ui_h80.h"
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
    QWidget *inputW,*outputW,*copyW,*h80W;
 
    //Ui::FormDev ui;
    Ui::DialogParam uiDlg;
    Ui::copyParam uiCopy;
    Ui::deviceParam uiDevIn,uiDevOut;
    Ui::H80Form uiH80;
};
#endif
