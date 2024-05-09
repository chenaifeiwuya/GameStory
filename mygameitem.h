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


class MainWindow;
class myGameItem: public QTableWidget
{
public:
    myGameItem();
public slots:
    void slot_setInfo(FileInfo & info);     //这里的FileInfo为游戏信息
    bool slot_setGameCover(int f_id, QString path);
    void Utf8ToGB2312( char* gbbuf , int nlen ,QString& utf8);
    QString GB2312ToUtf8(const char* gbbuf );
public:
    FileInfo m_info;
    QVBoxLayout *pLayout;   // = new QHBoxLayout();
    QLabel *pLabel;// = new QLabel();   //用于显示图片
    QLabel *p_text_Label;       //用于显示介绍的文字
    QString path;
    friend class MainWindow;
};

#endif // MYGAMEITEM_H



