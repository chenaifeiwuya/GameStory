#include "cstarpoint.h"
#include "ui_cstarpoint.h"

CStarPoint::CStarPoint(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::CStarPoint),
    point(0)
{
    ui->setupUi(this);
}

CStarPoint::~CStarPoint()
{
    delete ui;
}

#include <QPainter>
void CStarPoint::paintEvent(QPaintEvent *ev)
{
    QPainter painter(this);
    painter.drawPixmap(rect(),QPixmap(":/images/myimages/images/ysStar.png"),QRect());
}

void CStarPoint::on_pushButton_6_clicked()
{
    //判断point是否为0，若为0则自动改为1
    if(point == 0)
        point = 1;
    //然后将分数通过信号传出去
    emit SIG_GamePoint(point);
    this->close();
}

void CStarPoint::on_pushButton_clicked()
{
    point = 1;
    ui->pushButton->setIcon(QIcon(":/images/myimages/images/redStar.jpg"));
    ui->pushButton_2->setIcon(QIcon(":/images/myimages/images/whiteStar.png"));
    ui->pushButton_3->setIcon(QIcon(":/images/myimages/images/whiteStar.png"));
    ui->pushButton_4->setIcon(QIcon(":/images/myimages/images/whiteStar.png"));
    ui->pushButton_5->setIcon(QIcon(":/images/myimages/images/whiteStar.png"));

}

void CStarPoint::on_pushButton_2_clicked()
{
    point = 2;
    ui->pushButton->setIcon(QIcon(":/images/myimages/images/redStar.jpg"));
    ui->pushButton_2->setIcon(QIcon(":/images/myimages/images/redStar.jpg"));
    ui->pushButton_3->setIcon(QIcon(":/images/myimages/images/whiteStar.png"));
    ui->pushButton_4->setIcon(QIcon(":/images/myimages/images/whiteStar.png"));
    ui->pushButton_5->setIcon(QIcon(":/images/myimages/images/whiteStar.png"));
}

void CStarPoint::on_pushButton_3_clicked()
{
    point = 3;
    ui->pushButton->setIcon(QIcon(":/images/myimages/images/redStar.jpg"));
    ui->pushButton_2->setIcon(QIcon(":/images/myimages/images/redStar.jpg"));
    ui->pushButton_3->setIcon(QIcon(":/images/myimages/images/redStar.jpg"));
    ui->pushButton_4->setIcon(QIcon(":/images/myimages/images/whiteStar.png"));
    ui->pushButton_5->setIcon(QIcon(":/images/myimages/images/whiteStar.png"));
}

void CStarPoint::on_pushButton_4_clicked()
{
    point = 4;
    ui->pushButton->setIcon(QIcon(":/images/myimages/images/redStar.jpg"));
    ui->pushButton_2->setIcon(QIcon(":/images/myimages/images/redStar.jpg"));
    ui->pushButton_3->setIcon(QIcon(":/images/myimages/images/redStar.jpg"));
    ui->pushButton_4->setIcon(QIcon(":/images/myimages/images/redStar.jpg"));
    ui->pushButton_5->setIcon(QIcon(":/images/myimages/images/whiteStar.png"));
}

void CStarPoint::on_pushButton_5_clicked()
{
    point = 5;
    ui->pushButton->setIcon(QIcon(":/images/myimages/images/redStar.jpg"));
    ui->pushButton_2->setIcon(QIcon(":/images/myimages/images/redStar.jpg"));
    ui->pushButton_3->setIcon(QIcon(":/images/myimages/images/redStar.jpg"));
    ui->pushButton_4->setIcon(QIcon(":/images/myimages/images/redStar.jpg"));
    ui->pushButton_5->setIcon(QIcon(":/images/myimages/images/redStar.jpg"));
}
