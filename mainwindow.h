#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QMenu>
#include <QDebug>
#include <QFileDialog>
#include <QCloseEvent>
#include <QMessageBox>
#include <packdef.h>
#include <mytablewidgetitem.h>
#include <QProcess>
#include <QStringList>
#include <QInputDialog>
#include <mygameitem.h>
#include <gameintorduce.h>
#include <set>
#include <vector>
#include <QProcess>



#define GAME_COLUMNS 3

class cKernel;
namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = nullptr);
    ~MainWindow();
    void closeEvent(QCloseEvent* event)override;
    void getFileSize(int len);
    void slot_setcommentshow(int f_id,QStringList& nameList,QStringList& commentList,std::vector<int>& point);  //名字，评论，评分
    //void paintEvent(QPaintEvent* ev)override;
    void setPushbuttonStyle();

private slots:
    void on_pb_addfile_clicked();
    void slot_addFolder(bool flag);
    void slot_uploadFile(bool flag);
    void slot_uploadFolder(bool flag);
    void slot_getShare(bool flag);
    void slot_refreshPageInfo(bool flag);
    void slot_insertUploadFile(FileInfo& info);
    void slot_insertDownloadFile(FileInfo& info);
    void slot_insertUploadFileComplete(FileInfo& info);
    void slot_updateUploadFileProgress(int,int);
    void slot_deleteUploadFileByRow(int row);
    void slot_insertFileInfo(FileInfo& info);
    void slot_insertDownloadComplete(FileInfo &info);
    void slot_openPath(bool flag);
    void slot_deleteAllFileInfo();
    void slot_updateDownloadFileProgress(int,int);
    void slot_deleteDownloadFileByRow(int row);
    void slot_insertShareFileInfo(QString name, int size, QString time, int shareLink);
    void slot_deleteAllShareInfo();
    void slot_uploadPause(bool flag);
    void slot_uploadResume(bool flag);
    void slot_downloadPause(bool flag);
    void slot_downloadResume(bool flag);
    void slot_setName(QString name);
    FileInfo slot_getDownloadFileInfoByTimestamp(int timestamp);
    FileInfo slot_getUploadFileInfoByTimestamp(int timestamp);

    //显示每一个文件的传输速度
    void slot_showSpeed(std::map<int,FileInfo>& mp);
    //game story:
    void slot_deleteAllExploreGameInfo();
    void slot_insertExploreGameInfo(FileInfo &info);
    bool slot_insertGameInfo(int f_id, QString path);   //参数分别为文件id和文件的绝对路径
    void slot_setGameType(int f_id, QString type);    //设置游戏类型
    void slot_downloadGame(int f_id);   //根据f_id来下载游戏
    void slot_Sendcomment(int,QString,int);   //用于发表评论
    void slot_showCommentRes(int f_id,int flag);   //用于显示评论结果
    void slot_getcommentRq(int f_id, int num);  //获取评论
    void slot_removeIntroduce(int f_id);
    void slot_setGamedivide(int f_id, QString path,FileInfo& info);
    void slot_createGameIntroduce(int fileid,QString path);
    void slot_setDreamText(QString name,QString dreamText);
    void slot_sendUserMind(int);








    void on_pb_file_clicked();

    void on_pb_tranmit_clicked();



    //void on_table_file_clicked(const QModelIndex &index);

    void on_table_file_cellClicked(int row, int column);

    void on_table_file_customContextMenuRequested(const QPoint &pos);

    void slot_downloadFile(bool);
    void slot_shareFile(bool);
    void slot_deleteFile(bool);

    //void on_table_download_clicked(const QModelIndex &index);

    void on_table_download_cellClicked(int row, int column);

    void on_table_file_cellDoubleClicked(int row, int column);

    void on_pb_prev_clicked();

    void on_pb_share_clicked();


    void on_table_upload_cellClicked(int row, int column);

    void on_le_limit_editingFinished();



    void on_pb_store_clicked();

    void on_pb_hsz_clicked();

    void on_table_explore_clicked(const QModelIndex &index);

    void on_table_explore_itemClicked(QTableWidgetItem *item);

    void on_table_explore_cellClicked(int row, int column);

    void on_pushButton_2_clicked();

    void on_pushButton_3_clicked();

    void on_pushButton_4_clicked();

    void on_pushButton_6_clicked();

    void on_pushButton_5_clicked();

    void on_pushButton_7_clicked();

    void on_pushButton_8_clicked();

    void on_pushButton_9_clicked();

    void on_pushButton_10_clicked();

    void on_pushButton_11_clicked();

    void on_pushButton_12_clicked();

    void on_pushButton_13_clicked();

    void on_pushButton_14_clicked();

    void on_pushButton_15_clicked();

    void on_pushButton_16_clicked();

    void on_pushButton_17_clicked();

    void on_pushButton_clicked();

    void on_tab_gameDivide_cellDoubleClicked(int row, int column);

    void on_pushButton_18_clicked();

    void on_pb_sendDream_clicked();

signals:
    void SIG_uploadFile(QString,QString);    //第一个QString是需要上传的文件的路径， 第二个是希望保存到服务器的哪个目录下
    void SIG_close();
    void SIG_downloadFile(int ,QString);
    void SIG_downloadFolder(int ,QString);
    void SIG_addFolder(QString, QString);
    void SIG_changeDir(QString);
    void SIG_uploadFolder(QString, QString);
    void SIG_refreshPageInfo(QString);  //刷新当前页面信号
    void SIG_shareFile(QVector<int> ,QString);
    void SIG_getShareByLink(int,QString);
    void SIG_deleteFile(QVector<int> , QString);
    void SIG_getcommentRq(int f_id, int num);
    //设置上传暂停  0 开始  1暂停
    void SIG_setUploadPause(int timestamp, int isPause);
    //设置下载暂停 0开始  1暂停
    void SIG_setDownloadPause(int timestamp , int isPause);
    //更新上传下载进度
    void SIG_updateLimitSize(int newLimit);

    void SIG_getGameInfoFid(int fileid);

    void SIG_getGameType(int f_id);

    void SIG_downloadGame(int);   //根据fileid来下载游戏

    void SIG_downloadGameInfo(int,QString);   //下载游戏的外层信息,QString 可以为空

    void SIG_Sendcomment(int ,QString, int);


    void SIG_getGamedivideRq(int);   //int用于代表类型，用二进制表示

    void SIG_SelectGameByName(QString);    //通过游戏名来查找

    void SIG_getDream(int);   //用于获取心愿单

    void SIG_SendMyDream(QString text);   //用于发送我的心愿
    void SIG_SendUserMind(int);
private:
    Ui::MainWindow *ui;

    QMenu m_menuAddfile;
    QMenu m_menuFileInfo;
    QMenu m_menuDownload;
    QMenu m_menuUpload;


    std::map<int, myGameItem*> m_map_id_game;
    std::map<int,GameIntorduce*> m_map_id_gameInfo;
    std::set<int> m_gameInfo;//用于记录某个id对应的info是否下载过
    friend class cKernel;

    uint8_t columns;

    uint8_t gameStoryColumns;

    bool pbCheck[18];

     int dreamNum;   //当前已有的愿望数量


};

#endif // MAINWINDOW_H
