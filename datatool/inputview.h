#ifndef INPUT_VIEW_H
#define INPUT_VIEW_H
#include <QDialog>
#include <QString>
#include <QDebug>
#include <QMouseEvent>
#include <QMap>
#include <QStandardItemModel>
#include <QFileDialog>
#include "ui_inputoutput.h"
#include "QTapeIO.h"
#define DEVICE_DISK "DISKFILE"
#define DEVICE_TPIMG "TPIMG"
#define DEVICE_REEL "reel0000"

class inputView :public QWidget
{
    Q_OBJECT

public:
    inputView(QWidget *p);
    inputView(QWidget *p,int idd);
    ~inputView();
    void init();
    void setDev(QString in);
    void setTapes(QStringList list);
    void setOTapes(QStringList list);
    DEV getDev();
public   slots:
    void slotFileOpen();
    void slotComBox(const QString);
    
protected:
private:
    QString lastDir;
    int m_id;
    //bool _bSetTape; 
     
    Ui::FormDev ui;
};




#endif
