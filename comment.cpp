#include "comment.h"
#include "ui_comment.h"

comment::comment(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::comment)
{
    ui->setupUi(this);

    ui->star1->setIcon(QIcon(":/images/myimages/images/whiteStar.png"));
    ui->star2->setIcon(QIcon(":/images/myimages/images/whiteStar.png"));
    ui->star3->setIcon(QIcon(":/images/myimages/images/whiteStar.png"));
    ui->star4->setIcon(QIcon(":/images/myimages/images/whiteStar.png"));
    ui->star5->setIcon(QIcon(":/images/myimages/images/whiteStar.png"));

    //this->setFixedSize(200,100);

    this->setSizePolicy(QSizePolicy::Expanding,QSizePolicy::Expanding);

}

comment::~comment()
{
    delete ui;
}

void comment::setComment(QString name, QString commentText, int point)
{
    switch(point)
    {
    case 5:
        ui->star5->setIcon(QIcon(":/images/myimages/images/redStar.jpg"));
    case 4:
        ui->star4->setIcon(QIcon(":/images/myimages/images/redStar.jpg"));
    case 3:
        ui->star3->setIcon(QIcon(":/images/myimages/images/redStar.jpg"));
    case 2:
        ui->star2->setIcon(QIcon(":/images/myimages/images/redStar.jpg"));
    case 1:
        ui->star1->setIcon(QIcon(":/images/myimages/images/redStar.jpg"));
        break;
    default:
        break;
    }
    ui->name->setText(name);
    ui->commentText->setText(commentText);
    return;
}

void comment::setDream(QString name, QString dreamText)
{
    //隐藏评价
    ui->star5->hide();
    ui->star4->hide();
    ui->star3->hide();
    ui->star2->hide();
    ui->star1->hide();
    ui->label_2->hide();
    ui->name->setText(name);


    ui->commentText->setText(dreamText);
    ui->label->setStyleSheet("QLabel {background-color: transparent;}");
    ui->name->setStyleSheet("QLabel {background-color: transparent;}");
    ui->commentText->setStyleSheet("QLabel {background-color: transparent;}");
    return;
}

#include <QPainter>
void comment::paintEvent(QPaintEvent *ev)
{
    QPainter painter(this);
    painter.setOpacity(0.5);    //设置绘制时透明度为50%
    painter.drawPixmap(rect(),QPixmap(pixmappath),QRect());
}

void comment::setPixmapPath(int id)
{
    id  %= 10;
    char path[1000] = ":/images/myimages/images/ys1.png";
    path[strlen(path)-5] = '1'+id;
    pixmappath = QString(path);
}
