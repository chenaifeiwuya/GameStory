#ifndef MYGAMEITEM_H
#define MYGAMEITEM_H

#include <QTableWidgetItem>
#include <packdef.h>
#include <QVBoxLayout>
#include <QLabel>
#include <QWidget>
#include <QDir>
#include <QStringList>
#include <QPixmap>
#include <QPushButton>
#include <QTextStream>
#include <QTimer>


class MainWindow;
class myGameItem: public QTableWidget
{
public:
    myGameItem();
    myGameItem(int flag);    //用flag来对构造函数中要执行的功能进行分类
public slots:
    void slot_setInfo(FileInfo & info);     //这里的FileInfo为游戏信息
    bool slot_setGameCover(int f_id, QString path);
    void Utf8ToGB2312( char* gbbuf , int nlen ,QString& utf8);
    QString GB2312ToUtf8(const char* gbbuf );
    void startLoadImg();
    void setGameIcon();   //这里是设置仓库界面的游戏icon
public:
    FileInfo m_info;
    QVBoxLayout *pLayout;   // = new QHBoxLayout();
    QLabel *pLabel;// = new QLabel();   //用于显示图片
    QLabel *p_text_Label;       //用于显示介绍的文字
    QString path;
    QTimer timer;           //用于在仓库界面不断尝试加载游戏图片
    QString Text;       //文本
    friend class MainWindow;
};

#endif // MYGAMEITEM_H



