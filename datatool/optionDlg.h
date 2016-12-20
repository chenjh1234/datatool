#ifndef OPTION_DLG_H
#define OPTION_DLG_H
 
#include <QDialog>
#include <QString>
#include <QDebug>

#include <QFileDialog>
#include "ui_options.h"
 
class optionDlg : public QDialog
{
  
public:
    optionDlg(QWidget *p);
    ~optionDlg();
    void init();
    void setText(QString in);
    void setList(QStringList in);
    QString getText();
    QStringList getList();
    void setTitle(QString t);
    void setReadOnly();
public   slots:
 
 
private:
            
    Ui::DialogOption ui;
};
#endif
