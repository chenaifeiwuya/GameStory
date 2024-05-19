#ifndef GAMETYPE_H
#define GAMETYPE_H

#include <QWidget>
#include <set>

namespace Ui {
class GameType;
}

class GameType : public QWidget
{
    Q_OBJECT

public:
    explicit GameType(QWidget *parent = 0);
    ~GameType();
    void setFileId(int id);
signals:
    void SIG_sendGameType(char** buf, int num, int fileid, int typeNum);

private slots:
    void on_pushButton_clicked();

    void on_pushButton_2_clicked();

    void on_pushButton_3_clicked();

    void on_pushButton_4_clicked();

    void on_pushButton_15_clicked();

    void on_pushButton_7_clicked();

    void on_pushButton_5_clicked();

    void on_pushButton_6_clicked();

    void on_pushButton_16_clicked();

    void on_pushButton_14_clicked();

    void on_pushButton_20_clicked();

    void on_pushButton_17_clicked();

    void on_pushButton_8_clicked();

    void on_pushButton_18_clicked();

    void on_pushButton_9_clicked();

    void on_pushButton_22_clicked();

private:
    Ui::GameType *ui;
    bool checkState[6][4];    //用于区分某个按钮是否被选中
    int gameTypeNum;            //选中的游戏类型的数量
    std::set<std::string>set_GameType;
    int fileid;
    int typeNum;
   // bool isSend;  //用于判断当前是否发送type
};

#endif // GAMETYPE_H
