 #include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    m_sql = new CSqlite;

    InitDatabase(0);   //这里传的int参数是SQLite数据库名称
}

MainWindow::~MainWindow()
{
    delete ui;
}

#include <QDir>
#include <QDebug>
void MainWindow::InitDatabase(int id)
{
    //首先找到exe  去同级目录  创建数据文件 /datebase/id.db
    QString path = QCoreApplication::applicationDirPath() + "/datebase/";   //DirPath和FIlePath的区别！！
    QDir dir;
    if(!dir.exists(path)){   //如果不存在则创建
        dir.mkdir(path);
    }
    path = path + QString("%1.db").arg(id);

    QFileInfo info(path);
    if(info.exists())
    {
    //首先查看有没有这个文件
        //如果有的话则直接加载
            //连接
        m_sql->ConnectSql(path);
            //测试  读取数据
        /*
        QString sqlbuf = "select count(*) from t_upload;";
        QStringList lst;
        m_sql->SelectSql(sqlbuf, 1, lst);
        qDebug()<<"upload item count: "<<lst.front();
        lst.clear();

        sqlbuf = "select count(*) from t_download;";
        m_sql->SelectSql(sqlbuf, 1, lst);
        qDebug()<<"download item count: "<<lst.front();
        lst.clear();
        */

        QList<FileInfo> uploadTaskList;
        QList<FileInfo> downloadTaskList;

        slot_getUploadTask(uploadTaskList);
        slot_getDownloadTask(downloadTaskList);


    }else{
        //没有  创建表
        QFile file(path);
        if(!file.open( QIODevice::WriteOnly )) return;  //如果打开失败则返回
        file.close();
        //连接
        m_sql->ConnectSql(path);
        //创建表
        QString sqlbuf = "create table t_upload( \
                tiemestamp int,   \
                f_id int,   \
                f_name varchar(260), \
                f_dir varchar(260),  \
                f_time varchar(60),  \
                f_size int,  \
                f_md5 varchar(60),  \
                f_type varchar(60),  \
                f_absolutePath varchar(260))";
         m_sql->UpdateSql(sqlbuf);

        sqlbuf = "create table t_download( \
                tiemestamp int,    \
                f_id int,   \
                f_name varchar(260),   \
                f_dir varchar(260),   \
                f_time varchar(60),   \
                f_size int,          \
                f_md5 varchar(60),   \
                f_type varchar(60),  \
                f_absolutePath varchar(260)  \
                )";
         m_sql->UpdateSql(sqlbuf);

    }
}

void MainWindow::slot_writeUploadTask(FileInfo &info)
{
    QString sqlbuf = QString("insert into t_upload values(%1, %2, '%3', %4, '%4', '%5', %6, '%7','%8','%9');")\
                             .arg(info.timestamp) \
                             .arg(info.fileid)\
                            .arg(info.name)\
                            .arg(info.dir)\
                            .arg(info.time)\
                            .arg(info.size)\
                            .arg(info.md5)\
                            .arg(info.type)\
                            .arg(info.absolutePath);
}

void MainWindow::slot_writeDownloadTask(FileInfo &info)
{
    QString sqlbuf = QString("insert into t_download values(%1, %2, '%3', %4, '%4', '%5', %6, '%7','%8','%9');")\
                             .arg(info.timestamp) \
                             .arg(info.fileid)\
                            .arg(info.name)\
                            .arg(info.dir)\
                            .arg(info.time)\
                            .arg(info.size)\
                            .arg(info.md5)\
                            .arg(info.type)\
                            .arg(info.absolutePath);
}

void MainWindow::slot_deleteUploadTask(FileInfo &info)
{
    QString sqlbuf=QString("delete from t_upload where timestamp = %1;").arg(info.timestamp);
    m_sql->UpdateSql(sqlbuf);
}

void MainWindow::slot_deleteDownloadTask(FileInfo &info)
{
    QString sqlbuf=QString("delete from t_download where timestamp = %1 and f_absolutePath = '%2';")\
            .arg(info.timestamp)\
            .arg(info.absolutePath);
    m_sql->UpdateSql(sqlbuf);
}

void MainWindow::slot_getUploadTask(QList<FileInfo> &infoList)
{
       //获取所有的任务
    QString sqlbuf = "select * from t_upload;";
    QStringList lst;
    m_sql->SelectSql(sqlbuf, 9, lst);

    while(lst.size() != 0){
        FileInfo info;
        info.timestamp = QString(lst.front()).toInt(); lst.pop_front();
        info.fileid = QString(lst.front()).toInt(); lst.pop_front();
        info.name = lst.front(); lst.pop_front();
        info.dir = lst.front(); lst.pop_front();
        info.time = lst.front(); lst.pop_front();
        info.size =QString(lst.front()).toInt(); lst.pop_front();
        info.md5 = lst.front(); lst.pop_front();
        info.type = lst.front(); lst.pop_front();
        info.absolutePath = lst.front(); lst.pop_front();

        infoList.push_back(info);
    }
}

void MainWindow::slot_getDownloadTask(QList<FileInfo> &infoList)
{
    //获取所有的任务
 QString sqlbuf = "select * from t_download;";
 QStringList lst;
 m_sql->SelectSql(sqlbuf, 9, lst);

 while(lst.size() != 0){
     FileInfo info;
     info.timestamp = QString(lst.front()).toInt(); lst.pop_front();
     info.fileid = QString(lst.front()).toInt(); lst.pop_front();
     info.name = lst.front(); lst.pop_front();
     info.dir = lst.front(); lst.pop_front();
     info.time = lst.front(); lst.pop_front();
     info.size =QString(lst.front()).toInt(); lst.pop_front();
     info.md5 = lst.front(); lst.pop_front();
     info.type = lst.front(); lst.pop_front();
     info.absolutePath = lst.front(); lst.pop_front();

     infoList.push_back(info);
 }
}



//客户端数据库表   id.db
//表  正在上传
/*
create table t_upload(
        tiemestamp int,
        f_id int,
        f_name varchar(260),
        f_dir varchar(260),
        f_time varchar(60),
        f_size int,
        f_md5 varchar(60),
        f_type varchar(60),
        f_absolutePath(260)
        )

create table t_download(
        tiemestamp int,
        f_id int,
        f_name varchar(260),
        f_dir varchar(260),
        f_time varchar(60),
        f_size int,
        f_md5 varchar(60),
        f_type varchar(60),
        f_absolutePath(260)
        )
        */
//表  正在下载
