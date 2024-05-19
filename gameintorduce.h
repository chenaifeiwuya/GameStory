#ifndef GAMEINTORDUCE_H
#define GAMEINTORDUCE_H

#include <QWidget>
#include <QTimer>
#include <QLabel>
#include <QFile>
#include <QTextStream>
#include<QTextCodec>
#include <cstarpoint.h>
#include <QVBoxLayout>
#include "comment.h"

namespace Ui {
class GameIntorduce;
}

class GameIntorduce : public QWidget
{
    Q_OBJECT

public:
    explicit GameIntorduce(QWidget *parent = 0);
    ~GameIntorduce();
    void setGamePath(QString& path);
    void Utf8ToGB2312( char* gbbuf , int nlen ,QString& utf8);
    void setGameType(QString content);
    void setGameId(int f_id);   //设置游戏id
    void closeEvent(QCloseEvent *event) override;
    void slot_setcommentShow(int f_id,QStringList& nameList, QStringList& commentList, std::vector<int>& point);
    void paintEvent(QPaintEvent* ev)override;
public slots:
    void setGameInfoByPath();
private slots:
    void on_pb_right_clicked();

    void on_pb_left_clicked();

    void on_pushButton_clicked();

    void on_pb_getGame_clicked();


    void slot_GamePoint(int);  //获取评分
    void on_pb_Send_clicked();



    void on_pb_Send_2_clicked();

signals:
    void SIG_downloadGame(int f_id);   //根据f_id来下载游戏内容
    void SIG_Sendcomment(int f_id,QString content, int point);
    void SIG_getcommentRq(int f_id, int num);
    void SIG_removeIntroduce(int f_id);

private:
    Ui::GameIntorduce *ui;
    QVBoxLayout* comment_layout;
    QString path;
    QTimer timer;
    int imgIndex;  //当前在中间显示的是哪一张介绍图片
    QString imgLeft;
    QString imgMedium;
    QString imgRight;

    QPixmap pixmapMedium;
    QPixmap pixmapLeft;
    QPixmap pixmapRight;

    int flag;  //标志位，用于判断资源加载情况
    int f_id;                //当前游戏的f_id

    QLabel *textLabel;
    QString gameType;
    int point;  //该游戏的评分
    int commentNum;

    int m_height;

    int pixmapId;
};



#endif // GAMEINTORDUCE_H
