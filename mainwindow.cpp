#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QProgressBar>

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow),
    dreamNum(0)
{

    memset(pbCheck,0,sizeof(pbCheck));
    ui->setupUi(this);
    //默认文件分页
    ui->sw_page->setCurrentWidget(ui->page_file);
    //传输默认分页
    ui->tw_transmit->setCurrentWidget(ui->tab_upload);
    //设置标题栏
    this->setWindowTitle("我的网盘");
    //设置最小最大化
    this->setWindowFlags(Qt::WindowMinMaxButtonsHint|Qt::WindowCloseButtonHint);

    this->setStyleSheet("background-color: white;");  //设置无边框，设置背景为白色
    ui->page_file->setStyleSheet("QTableWidget {border: 0;backgroud-color:white}");  //设置无边框，设置背景为白色
    ui->page_share->setStyleSheet("QTableWidget {border: 0;backgroud-color:white}");
     ui->page_share->setStyleSheet("QWidget {border: 0;backgroud-color:white}");
    ui->page_rubsh->setStyleSheet("QTableWidget {border: 0;backgroud-color:white}");
    ui->page_story->setStyleSheet("QTableWidget {border: 0;backgroud-color:white}");
    ui->page_transmit->setStyleSheet("QTableWidget {border: 0;backgroud-color:white}");
    //首先定义菜单项   资源路径 :/(这里暂时不设置ICON)
    QAction * action_addFolder = new QAction(QString("新建文件夹"),this);
    QAction * action_uploadFie = new QAction(QString("上传文件"),this);
    QAction * action_uploadFolder = new QAction(QString("上传文件夹"),this);
    //添加菜单项
    m_menuAddfile.addAction(action_addFolder);
    m_menuAddfile.addSeparator();  //加入分隔符
    m_menuAddfile.addAction(action_uploadFie);
    m_menuAddfile.addAction(action_uploadFolder);

    connect(action_addFolder, SIGNAL(triggered(bool)), this, SLOT(slot_addFolder(bool)));    //triggered是非自定义信号
    connect(action_uploadFie, SIGNAL(triggered(bool)), this, SLOT(slot_uploadFile(bool)));
    connect(action_uploadFolder, SIGNAL(triggered(bool)), this, SLOT(slot_uploadFolder(bool)));


    //添加右键单击菜单项
    QAction * action_createFolder = new QAction(QString("新建文件夹"),this);
    QAction * action_downloadFile = new QAction(QString("下载文件"),this);
    QAction * action_shareFile = new QAction(QString("分享文件"),this);
    QAction * action_deleteFile = new QAction("删除文件",this);
    QAction * action_getShare = new QAction("获取分享文件",this);
    QAction * action_refresh = new QAction("刷新当前页面",this);

    m_menuFileInfo.addAction(action_createFolder);
    m_menuFileInfo.addAction(action_downloadFile);
    m_menuFileInfo.addAction(action_shareFile);
    m_menuFileInfo.addAction(action_deleteFile);
    m_menuFileInfo.addSeparator();  //加入分隔符
    m_menuFileInfo.addAction(action_getShare);
    m_menuFileInfo.addAction(action_refresh);

    connect(action_createFolder, SIGNAL(triggered(bool)), this, SLOT(slot_addFolder(bool)));
    connect(action_downloadFile, SIGNAL(triggered(bool)), this, SLOT(slot_downloadFile(bool)));    //triggered是非自定义信号(系统自带的)
    connect(action_shareFile, SIGNAL(triggered(bool)), this, SLOT(slot_shareFile(bool)));
    connect(action_deleteFile, SIGNAL(triggered(bool)), this, SLOT(slot_deleteFile(bool)));
    connect(action_getShare, SIGNAL(triggered(bool)), this, SLOT(slot_getShare(bool)));
    connect(action_refresh,SIGNAL(triggered(bool)),this,SLOT(slot_refreshPageInfo(bool)));
    ui->table_file->setContextMenuPolicy(Qt::CustomContextMenu);   //构造函数中添加此语句，使能待增加右键菜单功能的控件，否则在控件上无法弹出右键菜单；


    //添加右键显示菜单  lambda表达式  匿名函数
    //  []捕捉列表   ()函数参数列表  {}函数体     lambda表达式具体可以直接看官方文档
    connect(ui->table_download, &QTableWidget::customContextMenuRequested,this, [this](QPoint){this->m_menuDownload.exec(QCursor::pos());});
    connect(ui->table_upload,&QTableWidget::customContextMenuRequested,this,[this](QPoint){ this->m_menuUpload.exec(QCursor::pos()); });

    //添加菜单项
    QAction *actionUploadPause = new QAction("暂停",this);
    QAction *actionUploadResume = new QAction("开始",this);
    QAction *actionDownloadPause = new QAction("暂停",this);
    QAction *actionDownloadResume = new QAction("开始",this);

    m_menuUpload.addAction(actionUploadPause);
    m_menuUpload.addAction(actionUploadResume);
    m_menuUpload.addAction("全部暂停");
    m_menuUpload.addAction("全部开始");

    m_menuDownload.addAction(actionDownloadPause);
    m_menuDownload.addAction(actionDownloadResume);
    m_menuDownload.addAction("全部暂停");
    m_menuDownload.addAction("全部开始");

    connect(actionUploadPause,SIGNAL(triggered(bool)), this, SLOT(slot_uploadPause(bool)));
    connect(actionUploadResume,SIGNAL(triggered(bool)), this, SLOT(slot_uploadResume(bool)));
    connect(actionDownloadPause,SIGNAL(triggered(bool)), this, SLOT(slot_downloadPause(bool)));
    connect(actionDownloadResume,SIGNAL(triggered(bool)), this, SLOT(slot_downloadResume(bool)));
    ui->table_download->setContextMenuPolicy(Qt::CustomContextMenu);   //构造函数中添加此语句，使能待增加右键菜单功能的控件，否则在控件上无法弹出右键菜单；
    ui->table_upload->setContextMenuPolicy(Qt::CustomContextMenu);   //构造函数中添加此语句，使能待增加右键菜单功能的控件，否则在控件上无法弹出右键菜单；

    columns=0;
    gameStoryColumns=0;



    setPushbuttonStyle();

    ui->pushButton_18->hide();
    ui->pb_sendDream->hide();
    ui->text_Dream->hide();


}



MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::closeEvent(QCloseEvent *event)   //重写关闭事件
{
    if(QMessageBox::question(this,"退出提示","是否退出?") == QMessageBox::Yes)
    {
        //关闭
        event->accept();   //表示该事件已被处理，不用再向父类控件传递
        Q_EMIT SIG_close();
    }
    else
    {
        event->ignore();  //忽视该控件，向父类控件传递该事件
    }
}

//点击添加文件
void MainWindow::on_pb_addfile_clicked()
{
    //在鼠标点击坐标处 弹出菜单
    m_menuAddfile.exec(QCursor::pos());  //QCursor::pos():获取鼠标点击的坐标
}

//新建文件夹
void MainWindow::slot_addFolder(bool flag)
{
    qDebug()<<__func__;
    //弹出输入窗口
    QString name = QInputDialog::getText(this, "新建文件夹","输入名称");

    QString tmp = name;
    //空白符的处理
    if(name.isEmpty() || tmp.remove(" ").isEmpty() || name.length() > 100){
        QMessageBox::about(this, "提示","名字非法");
        return;
    }
    //不可以用的名字 ... 名字

    //一些非法  \ / : ? * < > | "    有的需要转义： \  "
    if(name.contains("\\") || name.contains("/") || name.contains(":") || name.contains("?") || name.contains("*") || name.contains("<")
            ||name.contains(">") || name.contains("|") || name.contains("\"")){
          QMessageBox::about(this,"提示","名字非法");
          return;
}
    //判断是否现在已经存在 todo
    QString dir = ui->lb_path->text();
    Q_EMIT SIG_addFolder(name, dir);

}

//上传文件
void MainWindow::slot_uploadFile(bool flag)
{
    qDebug()<<__func__;
    //弹出窗口 选择文件
    QString path = QFileDialog::getOpenFileName(this, "选择文件", "./");
    if(path.isEmpty()) return;  //如果路径为空，则说明没有选择文件，返回
    //目前上传的有没有一样的文件  如果是 取消  todo


    //发送信号  核心类处理  传递的信息：上传什么文件到  什么目录下
    QString dir = ui->lb_path->text();   //当前用户所在在服务器目录
    Q_EMIT SIG_uploadFile(path,dir);
}

//上传文件夹
extern int Dirflag;
void MainWindow::slot_uploadFolder(bool flag)
{
    qDebug()<<__func__;
    //点击 弹出文件选择对话框  选择路径
    QString path = QFileDialog::getExistingDirectory(this,"选择文件夹","./");
    //判断非空
    if(path.isEmpty()) return;
    //过滤 是否正在传 todo

    //发信号  上传什么路径的文件夹，到什么目录下面
    Dirflag = 1;
    Q_EMIT SIG_uploadFolder(path, ui->lb_path->text());

}

void MainWindow::slot_getShare(bool flag)
{
    qDebug()<<__func__;
    //弹窗 输入分享码
    QString txt = QInputDialog::getText(this,"获取分享","输入分享码");
    //过滤
    int code = txt.toInt();
    if(txt.length()!=9 || code<100000000 || code>=1000000000){
        QMessageBox::about(this,"提示","分享码非法");
        return;
    }
    //发送信号  什么目录下面  添加什么分享码的文件
    Q_EMIT SIG_getShareByLink(code, ui->lb_path->text());
}

void MainWindow::slot_refreshPageInfo(bool flag)
{
    qDebug()<<__func__;
    QString path = ui->lb_path->text();
    Q_EMIT SIG_refreshPageInfo(path);
}

//插入到上传中   (动态添加)
void MainWindow::slot_insertUploadFile(FileInfo &info)
{
    //表格插入信息
    //列：文件  大小  时间  网速 进度  暂停
    //1：新增一行  获取当前行+1  设置行数
    int rows = ui->table_upload->rowCount();   //获取控件当前行数
    ui->table_upload->setRowCount(rows+1);     //设置行数+1
    //2：设置这一行的每一列控件（添加对象）
    MyTableWidgetItem *item0=new MyTableWidgetItem;
    item0->slot_setInfo(info);
    ui->table_upload->setItem(rows, 0, item0);

    QTableWidgetItem *item1=new QTableWidgetItem(FileInfo::getSize(info.size));
    ui->table_upload->setItem(rows, 1, item1);

    QTableWidgetItem *item2=new QTableWidgetItem(info.time);
    ui->table_upload->setItem(rows, 2, item2);


    QTableWidgetItem *item3=new QTableWidgetItem("0kB");   //网速
    ui->table_upload->setItem(rows, 3, item3);
    //进度条
    QProgressBar* progress = new QProgressBar;
    progress->setMaximum(info.size);
    ui->table_upload->setCellWidget(rows, 4, progress);
    //暂停按钮
    QPushButton * button = new QPushButton;
    if(info.isPause){
            button->setText("开始");
        }
    else{
        button->setText("暂停");
    }
        ui->table_upload->setCellWidget(rows,5,button);

}

void MainWindow::slot_insertDownloadFile(FileInfo &info)
{
    //表格插入信息
    //列：文件  大小  时间  网速 进度  暂停
    //1：新增一行  获取当前行+1  设置行数
    int rows = ui->table_download->rowCount();   //获取控件当前行数
    ui->table_download->setRowCount(rows+1);     //设置行数+1
    //2：设置这一行的每一列控件（添加对象）
    MyTableWidgetItem *item0=new MyTableWidgetItem;
    item0->slot_setInfo(info);
    ui->table_download->setItem(rows, 0, item0);

    QTableWidgetItem *item1=new QTableWidgetItem(FileInfo::getSize(info.size));
    ui->table_download->setItem(rows, 1, item1);

    QTableWidgetItem *item2=new QTableWidgetItem(info.time);
    ui->table_download->setItem(rows, 2, item2);

    QTableWidgetItem *item3=new QTableWidgetItem("0kB");
    ui->table_download->setItem(rows, 3, item3);
    //进度条
    QProgressBar* progress = new QProgressBar;
    progress->setMaximum(info.size);
    ui->table_download->setCellWidget(rows, 4, progress);
    //暂停按钮
    QPushButton * button = new QPushButton;
    if(info.isPause){
            button->setText("开始");
        }
    else{
        button->setText("暂停");
    }
    ui->table_download->setCellWidget(rows,5,button);
}

void MainWindow::slot_insertUploadFileComplete(FileInfo &info)
{
    //列：文件名  大小 时间  上传完成
    //表格插入信息
    //1：新增一行  获取当前行+1  设置行数
    int rows = ui->table_complete->rowCount();
    ui->table_complete->setRowCount(rows +1);
    //2：设置这一行的每一列控件（添加对象）
    MyTableWidgetItem *item0=new MyTableWidgetItem;
    item0->slot_setInfo(info);
    ui->table_complete->setItem(rows, 0, item0);

    QTableWidgetItem *item1=new QTableWidgetItem(FileInfo::getSize(info.size));
    ui->table_complete->setItem(rows, 1, item1);

    QTableWidgetItem *item2=new QTableWidgetItem(info.time);
    ui->table_complete->setItem(rows, 2, item2);

    QTableWidgetItem *item3=new QTableWidgetItem("上传完成");
    ui->table_complete->setItem(rows, 3, item3);

}

void MainWindow::slot_updateUploadFileProgress(int timestamp, int pos)
{
    //遍历所有项  第0列
    int row = ui->table_upload->rowCount();
    for(int i=0;i<row;i++)
    {
        //取到每一个文件信息的时间戳  看是否一致
        MyTableWidgetItem* item0 = (MyTableWidgetItem*)ui->table_upload->item(i, 0);
        if(item0->m_info.timestamp == timestamp){
            //一致， 更新进度
            QProgressBar * item4=(QProgressBar*)ui->table_upload->cellWidget(i,4);
            item0->m_info.pos=pos;
            item4->setValue(pos);
            //看是否结束
            if(item4->value() >= item4->maximum()){
                //是，删除这一项  添加到已完成
                slot_deleteUploadFileByRow(i);
                slot_insertUploadFileComplete(item0->m_info);

                return;
            }
        }
    }

}

void MainWindow::slot_deleteUploadFileByRow(int row)
{

    return;
}

//获取文件列表然后插入到界面上
void MainWindow::slot_insertFileInfo(FileInfo &info)
{
    //列：文件名  大小 时间  上传完成
    //表格插入信息
    //1：新增一行  获取当前行+1  设置行数
    int rows = ui->table_file->rowCount();
    ui->table_file->setRowCount(rows +1);
    //2：设置这一行的每一列控件（添加对象）
    MyTableWidgetItem *item0=new MyTableWidgetItem;
    item0->slot_setInfo(info);
    ui->table_file->setItem(rows, 0, item0);

    myGameItem* Gameitem =new myGameItem(1);   //使用带参构造函数
    Gameitem->slot_setInfo(info);
    Gameitem->startLoadImg();    //开始尝试加载图片
    emit SIG_downloadGameInfo(info.fileid,"");   //QString 可以为空
    //发送信号获取该游戏的游戏信息
    ui->table_file->setCellWidget(rows,1,Gameitem);
    ui->table_file->resizeColumnsToContents();
    ui->table_file->resizeRowsToContents();


     myGameItem* item1 =new myGameItem(2);   //使用带参构造函数
    ui->table_file->setCellWidget(rows, 3, item1);

    QTableWidgetItem *item2=new QTableWidgetItem(info.time);
    ui->table_file->setItem(rows, 2, item2);

}

void MainWindow::slot_insertDownloadComplete(FileInfo &info)
{
    //列：文件名  大小 时间  上传完成
    //表格插入信息
    //1：新增一行  获取当前行+1  设置行数
    int rows = ui->table_complete->rowCount();
    ui->table_complete->setRowCount(rows +1);
    //2：设置这一行的每一列控件（添加对象）
    MyTableWidgetItem *item0=new MyTableWidgetItem;
    item0->slot_setInfo(info);
    ui->table_complete->setItem(rows, 0, item0);

    QTableWidgetItem *item1=new QTableWidgetItem(FileInfo::getSize(info.size));
    ui->table_complete->setItem(rows, 1, item1);
    //item1->setCheckState(Qt::Checked);

    QTableWidgetItem *item2=new QTableWidgetItem(info.time);
    ui->table_complete->setItem(rows, 2, item2);

    QPushButton* button=new QPushButton;
    button->setIcon(QIcon(":/images/myimages/images/folder.png"));
    button->setText("打开所在文件夹");
    //设置扁平
    button->setFlat(true);
    //tooltip 提示
    button->setToolTip(info.absolutePath);

    //tooltip 提示
    button->setToolTip(info.absolutePath);

    connect(button, SIGNAL(clicked(bool)), this, SLOT(slot_openPath(bool)));

    ui->table_complete->setCellWidget(rows, 3 ,button);
}


void MainWindow::slot_openPath(bool flag)
{
    QPushButton * button = (QPushButton *)QObject::sender();
    QString path = button->toolTip();

    // / 转化  \\ ...
    path.replace('/','\\');
    qDebug()<<path;
    //如何打开文件夹
    //exporer / select

    //通过Qt 打开进程
    QProcess process;
    QStringList lst;

    lst << QString("/select,")<<path;

    process.startDetached("explorer",lst);

}

//删除
void MainWindow::slot_deleteAllFileInfo()
{
    //ui->table_file->clear; //删文字  不用这个  行数不变

    int rows = ui->table_file->rowCount();
    for(int i=rows-1;i>=0;i--)
    {
        ui->table_file->removeRow(i);
    }
}

//更新下载的进度条
void MainWindow::slot_updateDownloadFileProgress(int pos, int timestamp)
{
    //遍历所有项  第0列
    int row = ui->table_download->rowCount();
    for(int i=0;i<row;i++)
    {
        //取到每一个文件信息的时间戳  看是否一致
        MyTableWidgetItem* item0 = (MyTableWidgetItem*)ui->table_download->item(i, 0);
        if(item0->m_info.timestamp == timestamp){
            //一致， 更新进度
            QProgressBar * item4=(QProgressBar*)ui->table_download->cellWidget(i,4);
            item0->m_info.pos=pos;
            item4->setValue(pos);
            //看是否结束
            if(item4->value() >= item4->maximum()){
                //是，删除这一项  添加到已完成
                slot_deleteDownloadFileByRow(i);
                slot_insertDownloadComplete(item0->m_info);

                return;
            }
        }
    }
}

void MainWindow::slot_deleteDownloadFileByRow(int row)
{
    return;
}

void MainWindow::slot_insertShareFileInfo(QString name, int size, QString time, int shareLink)
{
    //列：文件名  大小  时间  分享码
    //1:新增一行 获取当前行+1  设置行数
    int rows = ui->table_share->rowCount();
    ui->table_share->setRowCount(rows + 1);

    //2:设置这一行的每一列控件（添加对象）

    QTableWidgetItem *item0 = new QTableWidgetItem(name);
    ui->table_share->setItem(rows, 0, item0);

    QTableWidgetItem * item1 = new QTableWidgetItem(FileInfo::getSize(size));
    ui->table_share->setItem(rows,1,item1);

    QTableWidgetItem *item2=new QTableWidgetItem(time);
    ui->table_share->setItem(rows,2,item2);

    QTableWidgetItem * item3 = new QTableWidgetItem(QString::number(shareLink));
    ui->table_share->setItem(rows,3,item3);

}


void MainWindow::slot_deleteAllShareInfo()
{
    int rows = ui->table_share->rowCount();
    for(int i=rows-1; i>=0; i--)
    {
        ui->table_share->removeRow(i);
    }
}

void MainWindow::slot_uploadPause(bool flag)
{
    qDebug()<<"上传暂停";
    int rows = ui->table_upload->rowCount();
    //遍历表单
    for(int i=0;i<rows;++i){
        MyTableWidgetItem * item0 = (MyTableWidgetItem*)ui->table_upload->item(i,0);
        //看是否被选中
        if(item0->checkState() == Qt::Checked){
            QPushButton *button = (QPushButton *)ui->table_upload->cellWidget(i,5);
            //看按钮的状态 切换文字  发送信号
            if(button->text() == "暂停"){
                //信号  设置文件信息结构体暂停标志位
                button->setText("开始");
                Q_EMIT SIG_setUploadPause(item0->m_info.timestamp,1);
            }
        }
    }
}

void MainWindow::slot_uploadResume(bool flag)
{
    qDebug()<<"上传开始";
    int rows = ui->table_upload->rowCount();
    for(int i=0;i<rows;i++)
    {
        MyTableWidgetItem * item0 = (MyTableWidgetItem*)ui->table_upload->item(i,0);
        //看是否选中
        if(item0->checkState() == Qt::Checked)
        {
            QPushButton* button = (QPushButton*)ui->table_upload->cellWidget(i,5);
            //看按钮的状态  切换文字  发送信号
            if(button->text() == "开始")
            {
                button->setText("暂停");
                Q_EMIT SIG_setUploadPause(item0->m_info.timestamp,0);
            }
        }
    }
}

void MainWindow::slot_downloadPause(bool flag)
{
    qDebug()<<"下载暂停";
    int rows = ui->table_download->rowCount();
    for(int i=0;i<rows;i++)
    {
        MyTableWidgetItem * item0 = (MyTableWidgetItem*)ui->table_download->item(i,0);
        //看是否选中
        if(item0->checkState() == Qt::Checked)
        {
            QPushButton* button = (QPushButton*)ui->table_download->cellWidget(i,5);
            //看按钮的状态  切换文字  发送信号
            if(button->text() == "暂停")
            {
                button->setText("开始");
                Q_EMIT SIG_setDownloadPause(item0->m_info.timestamp,1);
            }
        }
    }
}

void MainWindow::slot_downloadResume(bool flag)
{
    qDebug()<<"下载开始";
    int rows = ui->table_download->rowCount();
    for(int i=0;i<rows;i++)
    {
        MyTableWidgetItem * item0 = (MyTableWidgetItem*)ui->table_download->item(i,0);
        //看是否选中
        if(item0->checkState() == Qt::Checked)
        {
            QPushButton* button = (QPushButton*)ui->table_download->cellWidget(i,5);
            //看按钮的状态  切换文字  发送信号
            if(button->text() == "开始")
            {
                button->setText("暂停");
                Q_EMIT SIG_setDownloadPause(item0->m_info.timestamp,0);
            }
        }
    }
}

void MainWindow::slot_setName(QString name)
{
    ui->pb_name->setText(name);
}

FileInfo MainWindow::slot_getDownloadFileInfoByTimestamp(int timestamp)
{
    //遍历所有第0列
    int rows = ui->table_download->rowCount();

    for(int i=0; i<rows; ++i){
        MyTableWidgetItem* item0=(MyTableWidgetItem *)ui->table_download->item(i,0);
        if(item0->m_info.timestamp == timestamp){
            return item0->m_info;
        }
    }
}

FileInfo MainWindow::slot_getUploadFileInfoByTimestamp(int timestamp)
{
    //遍历所有第0列
    int rows = ui->table_upload->rowCount();

    for(int i=0; i<rows; ++i){
        MyTableWidgetItem* item0=(MyTableWidgetItem *)ui->table_upload->item(i,0);
        if(item0->m_info.timestamp == timestamp){
            return item0->m_info;
        }
    }
}



void MainWindow::slot_showSpeed(std::map<int,FileInfo>&mp)
{
    //遍历所有第0列，查看时间戳能对上的

        int rows=ui->table_upload->rowCount();
        for(int i=0;i<rows; ++i)
        {
            MyTableWidgetItem* item0=(MyTableWidgetItem *)ui->table_upload->item(i,0);
            if(mp.count(item0->m_info.timestamp) > 0)
            {
                //只要map中存在，就更新其网速
                 int secondSize = mp[item0->m_info.timestamp].secondSize;
                 QString speedSize = FileInfo::getSize(secondSize);
                 QTableWidgetItem *item3 = (MyTableWidgetItem *)ui->table_upload->item(i,3);
                 speedSize = speedSize.mid(0,3) + speedSize.mid(speedSize.size()-3,3);
                 item3 ->setText(QString("%1/s").arg(speedSize));
                 mp[item0->m_info.timestamp].secondSize=0;   //显示完成后，当前秒的传输大小归0
            }

        }
}

void MainWindow::slot_deleteAllExploreGameInfo()
{
    int rows = ui->table_explore->rowCount();
    for(int i=rows-1;i>=0;i--)
    {
        ui->table_file->removeRow(i);
    }
}

void MainWindow::slot_insertExploreGameInfo(FileInfo &info)
{
    //表格插入信息
    //1：新增一行  获取当前行+1  设置行数
    int rows = ui->table_explore->rowCount();   //获取控件当前行数
    //查看当前添加到第几列了，每一列只能添加三个
    if(gameStoryColumns == 0)
    {
        //说明上一行已经添加满了，需要添加新的行数了
        ui->table_explore->setRowCount(rows+1);     //设置行数+1
    }

    if(++gameStoryColumns==3)
        gameStoryColumns=0;
    //在当前行的当前列添加item
    myGameItem *item = new myGameItem;
    item->slot_setInfo(info);
    ui->table_explore->setCellWidget(rows,gameStoryColumns,item);
    ui->table_explore->resizeColumnsToContents();
    ui->table_explore->resizeRowsToContents();

    /*
    ui->table_explore->setRowCount(rows+1);     //设置行数+1
    //2：设置这一行的每一列控件（添加对象）
    MyTableWidgetItem *item0=new MyTableWidgetItem;
    item0->slot_setInfo(info);
    ui->table_upload->setItem(rows, 0, item0);

    QTableWidgetItem *item1=new QTableWidgetItem(FileInfo::getSize(info.size));
    ui->table_upload->setItem(rows, 1, item1);

    QTableWidgetItem *item2=new QTableWidgetItem(info.time);
    ui->table_upload->setItem(rows, 2, item2);


    QTableWidgetItem *item3=new QTableWidgetItem("0kB");   //网速
    ui->table_upload->setItem(rows, 3, item3);
    //进度条
    QProgressBar* progress = new QProgressBar;
    progress->setMaximum(info.size);
    ui->table_upload->setCellWidget(rows, 4, progress);
    //暂停按钮
    QPushButton * button = new QPushButton;
    if(info.isPause){
            button->setText("开始");
        }
    else{
        button->setText("暂停");
    }
        ui->table_upload->setCellWidget(rows,5,button);
        */
}


//参数分别为文件id和绝对路径
bool MainWindow::slot_insertGameInfo(int f_id, QString path)
{

    /* int rows = ui->table_explore->rowCount();   //获取控件当前行数
     if(gameStoryColumns == 3)
         gameStoryColumns = 0;
    if(gameStoryColumns == 0)
             ui->table_explore->setRowCount(rows+1);     //设置行数+1
        myGameItem *item = new myGameItem;
        item->pLabel->setText("a");
        ui->table_explore->setCellWidget(rows,gameStoryColumns,item);
     gameStoryColumns++;
     return true;*/

    //根据路径，去找图片的介绍信息等等
    //QMessageBox::information(this,"info","您已经开始添加文件id和绝对路径了");
    if(m_map_id_game.count(f_id) > 0)
    {
        myGameItem* item = m_map_id_game[f_id];
        return item->slot_setGameCover(f_id,path);
    }

    QDir dir(path);
    QStringList fileList = dir.entryList(QStringList()<<"*.png", QDir::Dirs|QDir::Files);   //获得该路径下的图片，这个图片就是要加载到封面的图片



    //表格插入信息
    //1：新增一行  获取当前行+1  设置行数
    int rows = ui->table_explore->rowCount();   //获取控件当前行数
    //查看当前添加到第几列了，每一列只能添加三个
    if(gameStoryColumns==4)
        gameStoryColumns=0;
    if(gameStoryColumns == 0)
    {
        //说明上一行已经添加满了，需要添加新的行数了
        ui->table_explore->setRowCount(rows+1);     //设置行数+1
    }
    else rows-=1;


    //在当前行的当前列添加item
     //   gameStoryColumns = 0;
    myGameItem *item = new myGameItem;
        m_map_id_game[f_id]  = item;
    item->slot_setGameCover(f_id,path);
    ui->table_explore->setColumnWidth(gameStoryColumns,200);
    ui->table_explore->setRowHeight(rows,150);
    ui->table_explore->setCellWidget(rows,gameStoryColumns,item);
    item->show();
    ++gameStoryColumns;
   // ui->table_explore->resizeColumnsToContents();
    //ui->table_explore->resizeRowsToContents();
    return false;

}

void MainWindow::slot_setGameType(int f_id, QString type)
{
    //根据f_id找到窗口
    if(m_map_id_gameInfo.count(f_id) > 0)
    {
        GameIntorduce* widget = m_map_id_gameInfo[f_id];
        widget->setGameType(type);
    }
}

void MainWindow::slot_downloadGame(int f_id)
{
    emit SIG_downloadGame(f_id);
}

void MainWindow::slot_Sendcomment(int f_id, QString content, int point)
{
    emit SIG_Sendcomment(f_id,content,point);
}

void MainWindow::slot_showCommentRes(int f_id, int flag)
{
    //首先根据f_id找到对应的窗口
    if(m_map_id_gameInfo.count(f_id) > 0)
    {
        switch(flag)
        {
        case 0:
            QMessageBox::information(m_map_id_gameInfo[f_id],"res","评论失败，您尚未拥有该游戏!",QMessageBox::Ok);
            break;
        case 1:
            QMessageBox::information(m_map_id_gameInfo[f_id],"res","评论成功!",QMessageBox::Ok);
            break;
        case 2:
            QMessageBox::information(m_map_id_gameInfo[f_id],"res","评论失败，您已评论过该游戏，请勿重复评论!",QMessageBox::Ok);
            break;

        }
    }
}

void MainWindow::slot_getcommentRq(int f_id,int num)
{
    emit SIG_getcommentRq(f_id, num);
}

//设置评论显示

void MainWindow::slot_setcommentshow(int f_id,QStringList& nameList, QStringList& commentList, std::vector<int>& point)
{
    //首先通过id找到对应的introduce窗口
    if(m_map_id_gameInfo.count(f_id) > 0)
    {
        GameIntorduce* ite = m_map_id_gameInfo[f_id];
        if(ite != NULL)
        {
            ite->slot_setcommentShow(f_id,nameList,commentList,point);
        }
    }
    //窗口不存在则直接返回
    return;
}

void MainWindow::setPushbuttonStyle()
{
    //设置按钮样式
    ui->pushButton_2->setCheckable(true);  //设置为可选中
    ui->pushButton_2->setChecked(false);   //初始状态为未选中
    ui->pushButton_2->setStyleSheet("QPushButton { background-color: #ffffff; }"
                              "QPushButton:checked { background-color: #808080; }");

    //设置按钮样式
    ui->pushButton_3->setCheckable(true);  //设置为可选中
    ui->pushButton_3->setChecked(false);   //初始状态为未选中
    ui->pushButton_3->setStyleSheet("QPushButton { background-color: #ffffff; }"
                              "QPushButton:checked { background-color: #808080; }");

    //设置按钮样式
    ui->pushButton_4->setCheckable(true);  //设置为可选中
    ui->pushButton_4->setChecked(false);   //初始状态为未选中
    ui->pushButton_4->setStyleSheet("QPushButton { background-color: #ffffff; }"
                              "QPushButton:checked { background-color: #808080; }");

    //设置按钮样式
    ui->pushButton_5->setCheckable(true);  //设置为可选中
    ui->pushButton_5->setChecked(false);   //初始状态为未选中
    ui->pushButton_5->setStyleSheet("QPushButton { background-color: #ffffff; }"
                              "QPushButton:checked { background-color: #808080; }");

    //设置按钮样式
    ui->pushButton_6->setCheckable(true);  //设置为可选中
    ui->pushButton_6->setChecked(false);   //初始状态为未选中
    ui->pushButton_6->setStyleSheet("QPushButton { background-color: #ffffff; }"
                              "QPushButton:checked { background-color: #808080; }");

    //设置按钮样式
    ui->pushButton_7->setCheckable(true);  //设置为可选中
    ui->pushButton_7->setChecked(false);   //初始状态为未选中
    ui->pushButton_7->setStyleSheet("QPushButton { background-color: #ffffff; }"
                              "QPushButton:checked { background-color: #808080; }");

    //设置按钮样式
    ui->pushButton_8->setCheckable(true);  //设置为可选中
    ui->pushButton_8->setChecked(false);   //初始状态为未选中
    ui->pushButton_8->setStyleSheet("QPushButton { background-color: #ffffff; }"
                              "QPushButton:checked { background-color: #808080; }");

    //设置按钮样式
    ui->pushButton_9->setCheckable(true);  //设置为可选中
    ui->pushButton_9->setChecked(false);   //初始状态为未选中
    ui->pushButton_9->setStyleSheet("QPushButton { background-color: #ffffff; }"
                              "QPushButton:checked { background-color: #808080; }");

    //设置按钮样式
    ui->pushButton_10->setCheckable(true);  //设置为可选中
    ui->pushButton_10->setChecked(false);   //初始状态为未选中
    ui->pushButton_10->setStyleSheet("QPushButton { background-color: #ffffff; }"
                              "QPushButton:checked { background-color: #808080; }");

    //设置按钮样式
    ui->pushButton_11->setCheckable(true);  //设置为可选中
    ui->pushButton_11->setChecked(false);   //初始状态为未选中
    ui->pushButton_11->setStyleSheet("QPushButton { background-color: #ffffff; }"
                              "QPushButton:checked { background-color: #808080; }");

    //设置按钮样式
    ui->pushButton_12->setCheckable(true);  //设置为可选中
    ui->pushButton_12->setChecked(false);   //初始状态为未选中
    ui->pushButton_12->setStyleSheet("QPushButton { background-color: #ffffff; }"
                              "QPushButton:checked { background-color: #808080; }");

    //设置按钮样式
    ui->pushButton_13->setCheckable(true);  //设置为可选中
    ui->pushButton_13->setChecked(false);   //初始状态为未选中
    ui->pushButton_13->setStyleSheet("QPushButton { background-color: #ffffff; }"
                              "QPushButton:checked { background-color: #808080; }");

    //设置按钮样式
    ui->pushButton_14->setCheckable(true);  //设置为可选中
    ui->pushButton_14->setChecked(false);   //初始状态为未选中
    ui->pushButton_14->setStyleSheet("QPushButton { background-color: #ffffff; }"
                              "QPushButton:checked { background-color: #808080; }");

    //设置按钮样式
    ui->pushButton_15->setCheckable(true);  //设置为可选中
    ui->pushButton_15->setChecked(false);   //初始状态为未选中
    ui->pushButton_15->setStyleSheet("QPushButton { background-color: #ffffff; }"
                              "QPushButton:checked { background-color: #808080; }");
    //设置按钮样式
    ui->pushButton_16->setCheckable(true);  //设置为可选中
    ui->pushButton_16->setChecked(false);   //初始状态为未选中
    ui->pushButton_16->setStyleSheet("QPushButton { background-color: #ffffff; }"
                              "QPushButton:checked { background-color: #808080; }");

    //设置按钮样式
    //ui->pushButton_17->setCheckable(true);  //设置为可选中
   // ui->pushButton_17->setChecked(false);   //初始状态为未选中
  //  ui->pushButton_17->setStyleSheet("QPushButton { background-color: #ffffff; }"
   //                           "QPushButton:checked { background-color: #808080; }");
}


void MainWindow::slot_removeIntroduce(int f_id)
{
    if(m_map_id_gameInfo.count(f_id) > 0)
    {
        //移除
        m_map_id_gameInfo[f_id] = NULL;
        m_map_id_gameInfo.erase(f_id);
    }
    return;
}

//设置游戏 分类界面的游戏信息
void MainWindow::slot_setGamedivide(int f_id, QString path,FileInfo& info)
{
    //列：文件名  大小 时间  上传完成
    //表格插入信息
    //1：新增一行  获取当前行+1  设置行数
    //FileInfo info;
    info.fileid = f_id;
    info.absolutePath = path;
    int rows = ui->tab_gameDivide->rowCount();
    ui->tab_gameDivide->setRowCount(rows +1);
    //2：设置这一行的每一列控件（添加对象）
    MyTableWidgetItem *item0=new MyTableWidgetItem;
    item0->slot_setInfo(info);
    ui->tab_gameDivide->setItem(rows, 0, item0);

    myGameItem* Gameitem =new myGameItem(1);   //使用带参构造函数

    Gameitem->slot_setInfo(info);
    Gameitem->startLoadImg();    //开始尝试加载图片
    emit SIG_downloadGameInfo(info.fileid,"");   //QString 可以为空
    //发送信号获取该游戏的游戏信息
    ui->tab_gameDivide->setCellWidget(rows,1,Gameitem);
    ui->tab_gameDivide->resizeColumnsToContents();
    ui->tab_gameDivide->resizeRowsToContents();


    QTableWidgetItem *item1=new QTableWidgetItem(FileInfo::getSize(info.size));
    ui->tab_gameDivide->setItem(rows, 3, item1);

    QTableWidgetItem *item2=new QTableWidgetItem(info.time);
    ui->tab_gameDivide->setItem(rows, 2, item2);
}


//
void MainWindow::slot_createGameIntroduce(int fileid, QString path)
{
    //创建新页面，读取这个游戏的各种介绍信息
    GameIntorduce* window = new GameIntorduce;
    connect(window,SIGNAL(SIG_downloadGame(int)), this, SLOT(slot_downloadGame(int)));
    connect(window,SIGNAL(SIG_Sendcomment(int,QString,int)),this,SLOT(slot_Sendcomment(int,QString,int)));
    connect(window,SIGNAL(SIG_getcommentRq(int, int)),this,SLOT(slot_getcommentRq(int,int)));
    connect(window,SIGNAL(SIG_removeIntroduce(int)),this,SLOT(slot_removeIntroduce(int)));
    window->setGameId(fileid);
    window->setGamePath(path);
    if(m_map_id_gameInfo.count(fileid) == 0){    //没有下载过时才需要重新下载
        if(m_gameInfo.count(fileid) == 0){
            emit SIG_getGameInfoFid(fileid);
            m_gameInfo.insert(fileid);
        }
    }
    m_map_id_gameInfo[fileid] = window;
    emit SIG_getGameType(fileid);
    window->show();
}

void MainWindow::slot_setDreamText(QString name,QString dreamText)
{
    //将dream显示到界面上
    static int pixmapId=1;
    static int m_height;
    comment* newComment = new comment;
    newComment->setPixmapPath(pixmapId);
    pixmapId ++;
    newComment->setDream(name,dreamText);
    m_height += newComment->height();

    //ui->table_share->setFixedHeight(m_height);
    //comment_layout->addWidget(newComment);
    int row=ui->table_share->rowCount();
    ui->table_share->setRowCount(row +1);
    ui->table_share->setCellWidget(row,0,newComment);
    ui->table_share->resizeColumnsToContents();
    ui->table_share->resizeRowsToContents();

    newComment->show();
    dreamNum++;


}

void MainWindow::slot_sendUserMind(int mind)
{
    emit SIG_SendUserMind(mind);
}



void MainWindow::on_pb_file_clicked()
{
    ui->sw_page->setCurrentIndex(0);   //设置当前页面为文件页面
    ui->pushButton_18->hide();
    ui->pb_sendDream->hide();
    ui->text_Dream->hide();
}


void MainWindow::on_pb_tranmit_clicked()
{
    ui->sw_page->setCurrentIndex(1);   //设置当前页面为传输页面
    ui->pushButton_18->hide();
    ui->pb_sendDream->hide();
    ui->text_Dream->hide();
}




//左键单击选项
void MainWindow::on_table_file_cellClicked(int row, int column)  //实现选中行的时候切换前面的勾选空间的状态
{

    //切换勾选和未勾选状态
    if(column == 0){
        MyTableWidgetItem* item0=(MyTableWidgetItem*)ui->table_file->item(row,0);
        if(item0->checkState() == Qt::Checked)
            item0->setCheckState(Qt::Unchecked);
        else
            item0->setCheckState(Qt::Checked);
    }
    else if(column == 3){   //启动按钮
        //打开exe所在的文件夹然后启动
        MyTableWidgetItem* item0=(MyTableWidgetItem*)ui->table_file->item(row,0);
        QString path = item0->m_info.absolutePath;
        path.replace("/","\\");
        QProcess *process = new QProcess(this);
        QString program = "\""+path+"\\GAME\\game.exe"+"\"";// 替换为你的exe文件路径
        //QString program = QString("\"C:\\Users\\00\\Desktop\\GA ME\\game.exe\"");
        //QStringList command; // 如果需要传递参数，可以添加到这里
       // command << "\"" + path + "\"";
        //connect(process, &QProcess::readyReadStandardOutput, this, &YourClass::readStandardOutput);
        //connect(process, &QProcess::readyReadStandardError, this, &YourClass::readStandardError);
        //connect(process, static_cast<void (QProcess::*)(int, QProcess::ExitStatus)>(&QProcess::finished),
         //       this, &YourClass::onFinished);

        process->startDetached(program);
        QDir::setCurrent(QApplication::applicationDirPath());

    }

}

//右键单击选项
void MainWindow::on_table_file_customContextMenuRequested(const QPoint &pos)
{
    qDebug()<<__func__;
    m_menuFileInfo.exec(QCursor::pos());   //在鼠标座标处显示菜单
}

void MainWindow::slot_downloadFile(bool)
{
    qDebug()<<__func__;
    //遍历列表
    int rows = ui->table_file->rowCount();
    QString dir=ui->lb_path->text();  //获取目录
    for(int i=0;i<rows;++i){
        //看选中的
        MyTableWidgetItem* item0=(MyTableWidgetItem*)ui->table_file->item(i,0);
        if(item0->checkState() == Qt::Checked){
            //列表中有这个下载，不能开始 todo 过滤

            //获取类型
            if(item0->m_info.type == "file"){
                //发信号  下载文件  下载文件夹
                Q_EMIT SIG_downloadFile(item0->m_info.fileid , dir);
            }else{
                Q_EMIT SIG_downloadFolder(item0->m_info.fileid, dir);
            }
        }
    }
}

//分享文件槽函数
void MainWindow::slot_shareFile(bool)
{
    qDebug()<<__func__;
    //申请数组
    QVector<int> array;
    int count = ui->table_file->rowCount();
    //遍历所有项
    for(int i=0;i<count;++i){
        MyTableWidgetItem* item0=(MyTableWidgetItem*)ui->table_file->item(i,0);
        //看是否是打勾的
        if(item0->checkState() == Qt::Checked){
            //添加到数组里面
            array.push_back(item0->m_info.fileid);
        }
    }
    //发送信号
    Q_EMIT SIG_shareFile(array,ui->lb_path->text());

}

void MainWindow::slot_deleteFile(bool flag)
{
    qDebug()<<__func__;
    QVector<int> array;
    int count = ui->table_file->rowCount();
    for(int i=0; i<count;i++){
        MyTableWidgetItem * item0 = (MyTableWidgetItem *)ui->table_file->item(i,0);

        //看是否是打钩的
        if(item0->checkState() == Qt::Checked){
            //添加到数组里面
            array.push_back(item0->m_info.fileid);
        }
    }

    //发送信号
    Q_EMIT SIG_deleteFile(array, ui->lb_path->text());

}


void MainWindow::on_table_download_cellClicked(int row, int column)
{
    //单击后勾选上前面的勾
    //切换勾选和未勾选状态
    MyTableWidgetItem* item0=(MyTableWidgetItem*)ui->table_download->item(row,0);
    if(item0->checkState() == Qt::Checked)
        item0->setCheckState(Qt::Unchecked);
    else
        item0->setCheckState(Qt::Checked);
}


//双击某一行
void MainWindow::on_table_file_cellDoubleClicked(int row, int column)
{
    //首先拿到双击的那行的文件名字
    MyTableWidgetItem* item0 = (MyTableWidgetItem*)ui->table_file->item(row,0);
/*
    //判断是不是文件夹， 是文件夹可以跳转（是文件考虑打开文件todo）
    if(item0->m_info.type != "file"){
        //是文件夹  路径 拼接
        QString dir = ui->lb_path->text() + item0->m_info.name + "/";
        //设置路径 lb_path ->text
        ui->lb_path->setText(dir);
       // ui->lb_path->adjustSize();
        //发送信号 -> 更新当前的目录 -> 刷新文件列表
        Q_EMIT SIG_changeDir(dir);
    }*/

    //双击之后进入游戏界面
    //向服务器发送请求获取该游戏的介绍

    //创建新页面，读取这个游戏的各种介绍信息
    GameIntorduce* window = new GameIntorduce;
    connect(window,SIGNAL(SIG_downloadGame(int)), this, SLOT(slot_downloadGame(int)));
    connect(window,SIGNAL(SIG_Sendcomment(int,QString,int)),this,SLOT(slot_Sendcomment(int,QString,int)));
    connect(window,SIGNAL(SIG_getcommentRq(int, int)),this,SLOT(slot_getcommentRq(int,int)));
    connect(window,SIGNAL(SIG_removeIntroduce(int)),this,SLOT(slot_removeIntroduce(int)));
    window->setGameId(item0->m_info.fileid);
    window->setGamePath(item0->m_info.absolutePath);
    if(m_map_id_gameInfo.count(item0->m_info.fileid) == 0){    //没有下载过时才需要重新下载
        if(m_gameInfo.count(item0->m_info.fileid) == 0){
            emit SIG_getGameInfoFid(item0->m_info.fileid);
            m_gameInfo.insert(item0->m_info.fileid);
        }
    }
    m_map_id_gameInfo[item0->m_info.fileid] = window;
    emit SIG_getGameType(item0->m_info.fileid);
    window->show();
}

//返回上一级目录的按钮
void MainWindow::on_pb_prev_clicked()
{
    //获取目录
    QString path = ui->lb_path->text();
    //判断 ”/“结束
    if(path == "/")
        return;
    // /03/  left取多少个长度
    path = path.left(path.lastIndexOf("/"));   //-> /03

    //新的目录就是  找到的”/“以及左边的所有字符
    path = path.left(path.lastIndexOf("/")+1);  // /
    qDebug() << path;

    ui->lb_path->setText(path);
    //ui->lb_path->

    //跳转路径
    Q_EMIT SIG_changeDir(path);
}

void MainWindow::on_pb_share_clicked()
{
    ui->sw_page->setCurrentWidget(ui->page_share);
    ui->pushButton_18->show();
    ui->pb_sendDream->show();
    ui->text_Dream->show();
}



void MainWindow::on_table_upload_cellClicked(int row, int column)
{

    //单击后勾选上前面的勾
    //切换勾选和未勾选状态
    MyTableWidgetItem* item0=(MyTableWidgetItem*)ui->table_upload->item(row,0);
    if(item0->checkState() == Qt::Checked)
        item0->setCheckState(Qt::Unchecked);
    else
        item0->setCheckState(Qt::Checked);
}

void MainWindow::on_le_limit_editingFinished()
{
    QString limitSize = ui->le_limit->text();
    int size = atoi(limitSize.toStdString().c_str());
    Q_EMIT SIG_updateLimitSize(size);
}

void MainWindow::on_pb_store_clicked()
{
    ui->sw_page->setCurrentWidget(ui->page_story);
    ui->pushButton_18->hide();
    ui->pb_sendDream->hide();
    ui->text_Dream->hide();
}


#include "cmind.h"

void MainWindow::on_pb_hsz_clicked()
{
    /*
     * ui->sw_page->setCurrentWidget(ui->page_rubsh);
    ui->pushButton_18->hide();
    ui->pb_sendDream->hide();
    ui->text_Dream->hide();
    */


    //用于设置新界面用以设置用户情感
    CMind* m_mind = new CMind;
    connect(m_mind,SIGNAL(SIG_sendUserMind(int)),this,SLOT(slot_sendUserMind(int)));
    m_mind->show();
}


void MainWindow::on_table_explore_clicked(const QModelIndex &index)    //被点击了
{

}

void MainWindow::on_table_explore_itemClicked(QTableWidgetItem *item)
{

}

void MainWindow::on_table_explore_cellClicked(int row, int column)
{
    myGameItem* gameItem =(myGameItem*) ui->table_explore->cellWidget(row,column);
    //向服务器发送请求获取该游戏的介绍

    //创建新页面，读取这个游戏的各种介绍信息
    GameIntorduce* window = new GameIntorduce;
    connect(window,SIGNAL(SIG_downloadGame(int)), this, SLOT(slot_downloadGame(int)));
    connect(window,SIGNAL(SIG_Sendcomment(int,QString,int)),this,SLOT(slot_Sendcomment(int,QString,int)));
    connect(window,SIGNAL(SIG_getcommentRq(int,int)),this,SLOT(slot_getcommentRq(int,int)));
        connect(window,SIGNAL(SIG_removeIntroduce(int)),this,SLOT(slot_removeIntroduce(int)));
    window->setGameId(gameItem->m_info.fileid);
    window->setGamePath(gameItem->path);
    if(m_map_id_gameInfo.count(gameItem->m_info.fileid) == 0){    //没有下载过时才需要重新下载
        if(m_gameInfo.count(gameItem->m_info.fileid) == 0){
            emit SIG_getGameInfoFid(gameItem->m_info.fileid);
            m_gameInfo.insert(gameItem->m_info.fileid);
        }
    }
    m_map_id_gameInfo[gameItem->m_info.fileid] = window;
    emit SIG_getGameType(gameItem->m_info.fileid);
    window->show();
}

void MainWindow::on_pushButton_2_clicked()
{
    //获取当前状态
    /*if(pbCheck[2])
    {
        ui->pushButton_2->setChecked(false);
    }
    else{
        ui->pushButton_2->setChecked(true);

    }*/
     pbCheck[2] = !pbCheck[2];
}

void MainWindow::on_pushButton_3_clicked()
{
    pbCheck[3] = !pbCheck[3];
}

void MainWindow::on_pushButton_4_clicked()
{
    pbCheck[4] = !pbCheck[4];
}

void MainWindow::on_pushButton_5_clicked()
{
    pbCheck[5] = !pbCheck[5];
}

void MainWindow::on_pushButton_6_clicked()
{
    pbCheck[6] = !pbCheck[6];
}


void MainWindow::on_pushButton_7_clicked()
{
    pbCheck[7] = !pbCheck[7];
}

void MainWindow::on_pushButton_8_clicked()
{
    pbCheck[8] = !pbCheck[8];
}

void MainWindow::on_pushButton_9_clicked()
{
    pbCheck[9] = !pbCheck[9];
}

void MainWindow::on_pushButton_10_clicked()
{
    pbCheck[10] = !pbCheck[10];
}

void MainWindow::on_pushButton_11_clicked()
{
    pbCheck[11] = !pbCheck[11];
}

void MainWindow::on_pushButton_12_clicked()
{
    pbCheck[12] = !pbCheck[12];
}

void MainWindow::on_pushButton_13_clicked()
{
    pbCheck[13] = !pbCheck[13];
}

void MainWindow::on_pushButton_14_clicked()
{
    pbCheck[14] = !pbCheck[14];
}

void MainWindow::on_pushButton_15_clicked()
{
    pbCheck[15] = !pbCheck[15];
}

void MainWindow::on_pushButton_16_clicked()
{
    pbCheck[16] = !pbCheck[16];
}

void MainWindow::on_pushButton_17_clicked()
{
    //pbCheck[17] = !pbCheck[3];
    //先将原有数据清空
    int rows = ui->tab_gameDivide->rowCount();
    for(int i=rows-1;i>=0;i--)
    {
        ui->tab_gameDivide->removeRow(i);
    }
    //发送数据向服务器请求对应的数据
    unsigned int num = 0x01<<2;
    int res=0;
    for(int i=2; i<17; i++)
    {
        if(pbCheck[i])
        {
            res |= num;
        }
        num = num<<1;
    }
    emit SIG_getGamedivideRq(res);
}

void MainWindow::on_pushButton_clicked()
{
    //搜索游戏，显示出游戏窗口
    QString gameName = ui->lineEdit->text();
    emit SIG_SelectGameByName(gameName);

}

void MainWindow::on_tab_gameDivide_cellDoubleClicked(int row, int column)
{
    //首先拿到双击的那行的文件名字
    MyTableWidgetItem* item0 = (MyTableWidgetItem*)ui->table_file->item(row,0);
/*
    //判断是不是文件夹， 是文件夹可以跳转（是文件考虑打开文件todo）
    if(item0->m_info.type != "file"){
        //是文件夹  路径 拼接
        QString dir = ui->lb_path->text() + item0->m_info.name + "/";
        //设置路径 lb_path ->text
        ui->lb_path->setText(dir);
       // ui->lb_path->adjustSize();
        //发送信号 -> 更新当前的目录 -> 刷新文件列表
        Q_EMIT SIG_changeDir(dir);
    }*/

    //双击之后进入游戏界面
    //向服务器发送请求获取该游戏的介绍

    //创建新页面，读取这个游戏的各种介绍信息
    GameIntorduce* window = new GameIntorduce;
    connect(window,SIGNAL(SIG_downloadGame(int)), this, SLOT(slot_downloadGame(int)));
    connect(window,SIGNAL(SIG_Sendcomment(int,QString,int)),this,SLOT(slot_Sendcomment(int,QString,int)));
    connect(window,SIGNAL(SIG_getcommentRq(int, int)),this,SLOT(slot_getcommentRq(int,int)));
    connect(window,SIGNAL(SIG_removeIntroduce(int)),this,SLOT(slot_removeIntroduce(int)));
    window->setGameId(item0->m_info.fileid);
    window->setGamePath(item0->m_info.absolutePath);
    if(m_map_id_gameInfo.count(item0->m_info.fileid) == 0){    //没有下载过时才需要重新下载
        if(m_gameInfo.count(item0->m_info.fileid) == 0){
            emit SIG_getGameInfoFid(item0->m_info.fileid);
            m_gameInfo.insert(item0->m_info.fileid);
        }
    }
    m_map_id_gameInfo[item0->m_info.fileid] = window;
    emit SIG_getGameType(item0->m_info.fileid);
    window->show();
}


//该函数用于加载心愿
void MainWindow::on_pushButton_18_clicked()
{

    emit SIG_getDream(dreamNum);




}

void MainWindow::on_pb_sendDream_clicked()
{
    QString dreamText = ui->text_Dream->toPlainText();
    ui->text_Dream->setText("");
    emit SIG_SendMyDream(dreamText);
}
