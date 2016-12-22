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
    bool isCopyPrompt();
    bool isCopyToolbar();
    int getTapeBlock();
    void setTapeBlock(int len);
    void setCopyToolbar(bool b);
    void setCopyPrompt(bool b);

public   slots:
 
 
private:
            
    Ui::DialogOption ui;
};
#endif
