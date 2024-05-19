#include "gameintorduce.h"
#include "ui_gameintorduce.h"

GameIntorduce::GameIntorduce(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::GameIntorduce),
    flag(0),
    commentNum(0),
    m_height(0),
    pixmapId(0)
{
    ui->setupUi(this);
    //ui->widget->setSizePolicy(QSizePolicy::Expanding,QSizePolicy::Expanding);
    //textLabel = new QLabel;
    //ui->lay_introduce->addWidget(textLabel);
    //textLabel->show();
    comment_layout = new QVBoxLayout;
    ui->wdg_comment->setLayout(comment_layout);
    textLabel = ui->label_Text_2;
    ui->wdg_comment->setSizePolicy(QSizePolicy::Expanding,QSizePolicy::Expanding);

    //设置自动换行
    textLabel->setWordWrap(true);
    ui->lb_gametime->setText(gameType);
    connect(&timer,SIGNAL(timeout()),this,SLOT(setGameInfoByPath()));
}

GameIntorduce::~GameIntorduce()
{
    delete ui;
}

void GameIntorduce::setGamePath(QString& infopath)
{
    if(path != infopath) path = infopath;
    //设置路径后就启动定时器
    timer.setInterval(2000);  //间隔为2s
    timer.start();
}

#define IMG_LOAD_OVER (1)
#define TEXT_LOAD_OVER (2)


void GameIntorduce::setGameInfoByPath()
{
   //初始时，默认显示第一张图片
    imgIndex = 1;
    if(flag == 0 || flag==2){    //若顶部图片未加载完毕
        imgMedium = path + "/GAME_INTRODUCE_/img1.png";
        imgRight = path + "/GAME_INTRODUCE_/img2.png";

         //尝试加载图片并显示
         pixmapMedium.load(imgMedium,"PNG");
         if(pixmapMedium.isNull()) pixmapMedium.load(imgMedium,"JPG");
         pixmapRight.load(imgRight,"PNG");
         if(pixmapRight.isNull()) pixmapRight.load(imgRight,"JPG");

        if(!pixmapMedium.isNull() && !pixmapRight.isNull())
        {
            QSize newSize  = ui->main_Img->size();
            ui->main_Img->setPixmap(pixmapMedium.scaled(newSize,Qt::IgnoreAspectRatio,Qt::SmoothTransformation));
            newSize = ui->right_Img->size();
            ui->right_Img->setPixmap(pixmapRight.scaled(newSize,Qt::IgnoreAspectRatio,Qt::SmoothTransformation));
            flag |= IMG_LOAD_OVER;
        }
    }

    //尝试加载底部介绍
    if(flag==0 || flag==1){
        QString introducePath = path+"/GAME_INTRODUCE_/GAME.txt";
        QFile textFile(introducePath);
        if (!textFile.open(QIODevice::ReadOnly | QIODevice::Text)) {
            // 错误处理，文件未打开
            textLabel->setText("Error opening file.");
            return;
        }
        else
        {
            QTextStream in(&textFile);
            in.setCodec("UTF-8");
            QString content = in.readAll();  //读取整个文件
            textFile.close();
            textLabel->setText(content);


            textLabel->adjustSize();
            flag |= TEXT_LOAD_OVER;
        }
    }

    //若全部加载完毕，则关闭定时器
    if(flag&TEXT_LOAD_OVER!=0 && flag&IMG_LOAD_OVER!=0)
    {
        timer.stop();
    }


}


void GameIntorduce::Utf8ToGB2312( char* gbbuf , int nlen ,QString& utf8)
{
    //转码的对象
    QTextCodec * gb2312code = QTextCodec::codecForName( "gb2312");
    //QByteArray char 类型数组的封装类 里面有很多关于转码 和 写IO的操作
    QByteArray ba = gb2312code->fromUnicode( utf8 );// Unicode -> 转码对象的字符集

    strcpy_s ( gbbuf , nlen , ba.data() );
}

void GameIntorduce::setGameType(QString content)
{
    gameType = content;
    ui->lb_gametime->setText(content);
}

void GameIntorduce::setGameId(int f_id)
{
    this->f_id = f_id;
}

void GameIntorduce::closeEvent(QCloseEvent *event)
{
    //发送信号让mainwindow移除map中对应的信息
    emit SIG_removeIntroduce(f_id);
}

//用于将玩家的评论添加到界面上
void GameIntorduce::slot_setcommentShow(int f_id, QStringList& nameList, QStringList& commentList, std::vector<int>& point)
{
    int num = point.size();
    for(int i=0; i<num; i++)
    {
        comment* newComment = new comment;
        newComment->setPixmapPath(pixmapId);
        pixmapId ++;
        newComment->setComment(nameList.front(),commentList.front(),point[i]);
        m_height += newComment->height();
        ui->wdg_comment->setFixedHeight(m_height);
        comment_layout->addWidget(newComment);
        newComment->show();
        commentNum++;

        nameList.pop_front();;
        commentList.pop_front();

    }
}

#include <QPainter>
void GameIntorduce::paintEvent(QPaintEvent *ev)
{
    QPainter painter(this);
     painter.setOpacity(0.5);    //设置绘制时透明度为50%
    painter.drawPixmap(rect(),QPixmap(":/images/myimages/images/ys.png"),QRect());
}




void GameIntorduce::on_pb_right_clicked()
{
    //显示的图片向右传递
    int position = imgRight.indexOf(".png");
    if(position == -1)   //没找到
    {
         return;
    }

    //imgRight[position] += 1;  //尝试是否有此文件
    //imgRight.replace(position-1,1,imgRight.at(position-1)+1);
    QString imgTest = imgRight;
    std::string str = imgTest.toStdString();
    str[position-1] += 1;
    imgTest = QString::fromStdString(str);
    QFile file(imgTest);
    if(!file.exists())
    {
        //不存在则回到1
        str[position-1] = '1';
        imgTest = QString::fromStdString(str);
    }
    file.close();
    QPixmap pixTest;
    pixTest.load(imgTest,"PNG");
    if(pixTest.isNull()) pixTest.load(imgTest,"JPG");
    if(pixTest.isNull()) return;   //如果仍然加载失败，则退出

    //加载成功则继续
    pixmapLeft = pixmapMedium;
    pixmapMedium = pixmapRight;
    pixmapRight = pixTest;

    imgLeft = imgMedium;
    imgMedium = imgRight;
    imgRight = imgTest;

        QSize newSize  = ui->main_Img->size();
        ui->main_Img->setPixmap(pixmapMedium.scaled(newSize,Qt::IgnoreAspectRatio,Qt::SmoothTransformation));
        newSize = ui->right_Img->size();
        ui->right_Img->setPixmap(pixmapRight.scaled(newSize,Qt::IgnoreAspectRatio,Qt::SmoothTransformation));
        newSize = ui->left_Img->size();
        ui->left_Img->setPixmap(pixmapLeft.scaled(newSize,Qt::IgnoreAspectRatio,Qt::SmoothTransformation));
}

void GameIntorduce::on_pb_left_clicked()
{

    //显示的图片向左传递
    int position = imgLeft.indexOf(".png");
    if(position == -1)   //没找到
    {
         return;
    }

    //imgRight[position] += 1;  //尝试是否有此文件
    //imgRight.replace(position-1,1,imgRight.at(position-1)+1);
    QString imgTest = imgLeft;
    std::string str = imgTest.toStdString();
    str[position-1] -= 1;
    imgTest = QString::fromStdString(str);
    QFile file(imgTest);
    if(!file.exists())
    {
        //不存在则不变
        imgTest = imgLeft;

    }
    file.close();
    QPixmap pixTest;
    pixTest.load(imgTest,"PNG");
    if(pixTest.isNull()) pixTest.load(imgTest,"JPG");
    if(pixTest.isNull()) return;   //如果仍然加载失败，则退出

    //加载成功则继续
    pixmapRight = pixmapMedium;
    pixmapMedium = pixmapLeft;
    pixmapLeft = pixTest;

    imgRight = imgMedium;
    imgMedium = imgLeft;
    imgLeft = imgTest;

        QSize newSize  = ui->main_Img->size();
        ui->main_Img->setPixmap(pixmapMedium.scaled(newSize,Qt::IgnoreAspectRatio,Qt::SmoothTransformation));
        newSize = ui->right_Img->size();
        ui->right_Img->setPixmap(pixmapRight.scaled(newSize,Qt::IgnoreAspectRatio,Qt::SmoothTransformation));
        newSize = ui->left_Img->size();
        ui->left_Img->setPixmap(pixmapLeft.scaled(newSize,Qt::IgnoreAspectRatio,Qt::SmoothTransformation));
}


//该槽函数用于加载评论
void GameIntorduce::on_pushButton_clicked()
{
    //发送信号让kernel发出加载评论的请求
    emit SIG_getcommentRq(f_id,commentNum);
}

void GameIntorduce::on_pb_getGame_clicked()
{
    //下载游戏
    emit SIG_downloadGame(f_id);
}

#include <QMessageBox>
void GameIntorduce::slot_GamePoint(int gamePoint)
{
    point = gamePoint;
    //获取评论框里的评论，然后发送给服务器
    QString text = ui->lineEdit_2->text();
    QString copy(text.remove(" "));
    if(copy.isEmpty()){
        QMessageBox::warning(this,"提示","评论不能为空！",QMessageBox::Ok);
        return;    //去掉空格后为空就不发送
    }

    emit SIG_Sendcomment(f_id,text,point);
}

void GameIntorduce::on_pb_Send_clicked()
{

}


void GameIntorduce::on_pb_Send_2_clicked()
{
    CStarPoint* starPoint = new CStarPoint;
    connect(starPoint,SIGNAL(SIG_GamePoint(int)),this,SLOT(slot_GamePoint(int)));
        starPoint->show();
}
