#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <packdef.h>
#include "csqlite.h"

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();

    //登陆之后，初始化数据
    void InitDatabase(int id);
public slots:
    //缓存上传的任务
    void slot_writeUploadTask(FileInfo & info);
    //缓存下载的任务
    void slot_writeDownloadTask(FileInfo & info);
    //完成任务，删除上传记录
    void slot_deleteUploadTask(FileInfo & info);
    //完成任务，删除下载任务
    void slot_deleteDownloadTask(FileInfo & info);
    //加载上传任务
    void slot_getUploadTask(QList<FileInfo> &infoList);
    //加载下载任务
    void slot_getDownloadTask(QList<FileInfo> &infoList);



private:
    Ui::MainWindow *ui;

    CSqlite* m_sql;

};

#endif // MAINWINDOW_H
