#ifndef EDITDLG_H
#define EDITDLG_H
 
#include <QDialog>
#include <QString>
#include <QDebug>

#include <QFileDialog>
#include "ui_textedit.h"
 
class editDlg : public QDialog
{
  
public:
    editDlg(QWidget *p);
    ~editDlg();
    void init();
    void setText(QString in);
    void setList(QStringList in);
    QString getText();
    QStringList getList();
    void setTitle(QString t);
    void setReadOnly();
public   slots:
 
 
private:
            
    Ui::Dialog ui;
};
#endif
