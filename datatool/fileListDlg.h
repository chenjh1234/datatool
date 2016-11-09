#ifndef FILE_LIST_DLG_H
#define FILE_LIST_DLG_H
 
#include <QDialog>
#include <QString>
#include <QStringList>
#include <QDebug>
#include <QTreeWidgetItem>
#include <QFileDialog>
#include "ui_fileList.h"
#define FILE_NAME 0
#define FILE_SIZE 1
#define FILE_LASTMODIFY 2

#define MOVE_UP 0
#define MOVE_DOWN 1
#define MOVE_REMOVE 2
   
class fileListDlg :public QDialog
{
    Q_OBJECT
public:
    fileListDlg(QWidget *p);
    ~fileListDlg();
    void init();
    void addItem(QStringList it);
    QStringList getList();
    void moveSelectedItem(int where);
    QStringList listZF;  

public   slots:
    void slotAdd();
    void slotRemove();
    void slotUp();
    void slotDown();
    void slotClear();
    void slotUnselect();

private:
    QString lastDir;
      // file size = 0;
    Ui::DialogFileList ui;
};
#endif

