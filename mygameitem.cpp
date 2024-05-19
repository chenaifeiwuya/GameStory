#include "mygameitem.h"


myGameItem::myGameItem()
{
    //this->setFixedSize(100,200);
    pLayout = new QVBoxLayout;
  //  pLayout->setMargin();
    pLabel = new QLabel();
    pLabel->setObjectName("GameIcon");
    //pLabel->setText("this is a game");
    pLabel->setFixedSize(150,130);
    pLabel->setMaximumHeight(130);
    pLabel->setMaximumWidth(190);
    pLabel->show();
   // pLabel->setFixedSize(100*200);

    p_text_Label = new QLabel();
    p_text_Label->setObjectName(("GameText"));
    p_text_Label->show();
    pLayout->addWidget(pLabel);
    pLayout->addWidget(p_text_Label);
    this->setLayout(pLayout);
}

myGameItem::myGameItem(int flag)
{
    if(flag == 1){
        pLayout = new QVBoxLayout;
      //  pLayout->setMargin();
        pLabel = new QLabel();
        pLabel->setObjectName("GameIcon");
        //pLabel->setText("this is a game");
        pLabel->setFixedSize(100,70);
        pLabel->setMaximumHeight(70);
        pLabel->setMaximumWidth(100);
        pLabel->show();
       // pLabel->setFixedSize(100*200);
        pLayout->addWidget(pLabel);
        this->setLayout(pLayout);
        this->setMaximumWidth(100);
        this->setMaximumHeight(70);
    }
    else if(flag == 2)
    {
        pLayout = new QVBoxLayout;
      //  pLayout->setMargin();
        pLabel = new QLabel();
        pLabel->setObjectName("GameIcon");
        //pLabel->setText("this is a game");
        pLabel->setFixedSize(500,70);
        pLabel->setMaximumHeight(70);
        pLabel->setMaximumWidth(500);
        pLabel->show();
       // pLabel->setFixedSize(100*200);
        pLayout->addWidget(pLabel);
        this->setLayout(pLayout);
        this->setMaximumWidth(500);
        this->setMaximumHeight(70);



        QPixmap pixmap(":/images/myimages/images/start.png");
        //设置QLabel背景图像为该JPG图片
        if(pixmap.isNull())
            return ;
        QSize newSize=pLabel->size();
        //QSize size(newSize.width()-10,newSize.height()-20);
        pLabel->setPixmap(pixmap.scaled(newSize,Qt::IgnoreAspectRatio, Qt::SmoothTransformation));
        //调整控件大小以适应图片尺寸
        pLabel->setScaledContents(true); // 如果需要，设置QLabel自动缩放内容以适应其大小
    }
    else if(flag == 3)
    {
        //显示文字
    }
}

void myGameItem::slot_setInfo(FileInfo &info)
{

    m_info = info;
/*
  //  this->setText(info.name);

    if(info.type != "file"){
        //设置游戏封面   游戏封面由独立的file构成
        //在缓存文件夹中找到当前文件的缓存信息
        QString infoPath = QString(info.absolutePath);
        //打开该文件夹
        QDir gameInfoDir(infoPath);
        if(gameInfoDir.exists())   //文件夹存在
        {
            QStringList fileList = gameInfoDir.entryList(QDir::Files | QDir::Dirs);
            //判断当前获取的是否是文件夹
            foreach(const QString &str, fileList) {
                if(QString("gameImg") == str)
                {
                    //图片信息
                    //加载封面图片
                    QPixmap pixmap(infoPath + "\gameImg" + "\1.jpg");
                    // 设置QLabel背景图像为该JPG图片
                    pLabel->setPixmap(pixmap);
                    // 调整控件大小以适应图片尺寸
                    pLabel->resize(pixmap.width(), pixmap.height());
                }
            }
        }
        else  //文件夹不存在
        {
            return;
        }
    }
*/
    //不设置勾选框
}

bool myGameItem::slot_setGameCover(int f_id, QString path)
{
    //根据获得的路径将封面显示出来,并将对应的数据保存
    m_info.fileid = f_id;
    m_info.absolutePath = path;
    this->path = path;
    QDir dir(path);
    QStringList filters;
    filters <<"*.png"<<"*.jpg";   //添加png和jpg的过滤条件
    QStringList fileList = dir.entryList(filters, QDir::Files);
    if(!fileList.empty())
    {
        path += "/";
        path += fileList.front();

        QPixmap pixmap(path);
        //设置QLabel背景图像为该JPG图片
        if(pixmap.isNull())
            return false;
        QSize newSize=pLabel->size();
        //QSize size(newSize.width()-10,newSize.height()-20);
        pLabel->setPixmap(pixmap.scaled(newSize,Qt::IgnoreAspectRatio, Qt::SmoothTransformation));
        //调整控件大小以适应图片尺寸
        pLabel->setScaledContents(true); // 如果需要，设置QLabel自动缩放内容以适应其大小
        //pLabel->resize(pixmap.width(), pixmap.height());
        //pLabel->show();

        QString name = fileList.front();
        name.remove(".png");
        p_text_Label->setText(name);
        p_text_Label->setAlignment(Qt::AlignCenter);
        p_text_Label->setStyleSheet("QLabel { background-color: cyan; }");
       // p_text_Label->show();
    }




    //然后显示游戏名称


    return true;


}

#include<QTextCodec>

// QString -> char* gb2312
void myGameItem::Utf8ToGB2312( char* gbbuf , int nlen ,QString& utf8)
{
    //转码的对象
    QTextCodec * gb2312code = QTextCodec::codecForName( "gb2312");
    //QByteArray char 类型数组的封装类 里面有很多关于转码 和 写IO的操作
    QByteArray ba = gb2312code->fromUnicode( utf8 );// Unicode -> 转码对象的字符集

    strcpy_s ( gbbuf , nlen , ba.data() );
}

QString myGameItem::GB2312ToUtf8(const char* gbbuf )
{
    //转码的对象
    QTextCodec * gb2312code = QTextCodec::codecForName( "gb2312");
    //QByteArray char 类型数组的封装类 里面有很多关于转码 和 写IO的操作
    return gb2312code->toUnicode( gbbuf );// 转码对象的字符集 -> Unicode
}

void myGameItem::startLoadImg()
{
    timer.setInterval(2000);  //2s钟尝试一次
    connect(&timer,&QTimer::timeout,this,&myGameItem::setGameIcon);
    timer.start();
}

void myGameItem::setGameIcon()
{
    //根据获得的路径将封面显示出来,并将对应的数据保存
    this->path = m_info.absolutePath;
    QDir dir(path);
    QStringList filters;
    filters <<"*.png"<<"*.jpg";   //添加png和jpg的过滤条件
    QStringList fileList = dir.entryList(filters, QDir::Files);
    if(!fileList.empty())
    {
        path += "/";
        path += fileList.front();

        QPixmap pixmap(path);
        //设置QLabel背景图像为该JPG图片
        if(pixmap.isNull())
            return;
        QSize newSize=pLabel->size();
        //QSize size(newSize.width()-10,newSize.height()-20);
        pLabel->setPixmap(pixmap.scaled(newSize,Qt::IgnoreAspectRatio, Qt::SmoothTransformation));
        //调整控件大小以适应图片尺寸
        pLabel->setScaledContents(true); // 如果需要，设置QLabel自动缩放内容以适应其大小
        //如果加载成功，则定时器停止
        timer.stop();
    }
}

