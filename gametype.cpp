#include "gametype.h"
#include "ui_gametype.h"
#include <QMessageBox>

GameType::GameType(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::GameType),
    gameTypeNum(0),
    typeNum(0)
{
    ui->setupUi(this);
    memset(checkState,1,sizeof(checkState));
    ui->pushButton->setCheckable(true); // 设置为可选中
    ui->pushButton->setChecked(false); // 初始状态为未选中
    ui->pushButton->setStyleSheet("QPushButton { background-color: #ffffff; }"
                              "QPushButton:checked { background-color: #808080; }");


    ui->pushButton_2->setCheckable(true); // 设置为可选中
    ui->pushButton_2->setChecked(false); // 初始状态为未选中
    ui->pushButton_2->setStyleSheet("QPushButton { background-color: #ffffff; }"
                              "QPushButton:checked { background-color: #808080; }");

    ui->pushButton_3->setCheckable(true); // 设置为可选中
    ui->pushButton_3->setChecked(false); // 初始状态为未选中
    ui->pushButton_3->setStyleSheet("QPushButton { background-color: #ffffff; }"
                              "QPushButton:checked { background-color: #808080; }");

    ui->pushButton_15->setCheckable(true); // 设置为可选中
    ui->pushButton_15->setChecked(false); // 初始状态为未选中
    ui->pushButton_15->setStyleSheet("QPushButton { background-color: #ffffff; }"
                              "QPushButton:checked { background-color: #808080; }");

    ui->pushButton_4->setCheckable(true); // 设置为可选中
    ui->pushButton_4->setChecked(false); // 初始状态为未选中
    ui->pushButton_4->setStyleSheet("QPushButton { background-color: #ffffff; }"
                              "QPushButton:checked { background-color: #808080; }");

    ui->pushButton_5->setCheckable(true); // 设置为可选中
    ui->pushButton_5->setChecked(false); // 初始状态为未选中
    ui->pushButton_5->setStyleSheet("QPushButton { background-color: #ffffff; }"
                              "QPushButton:checked { background-color: #808080; }");

    ui->pushButton_6->setCheckable(true); // 设置为可选中
    ui->pushButton_6->setChecked(false); // 初始状态为未选中
    ui->pushButton_6->setStyleSheet("QPushButton { background-color: #ffffff; }"
                              "QPushButton:checked { background-color: #808080; }");

    ui->pushButton_7->setCheckable(true); // 设置为可选中
    ui->pushButton_7->setChecked(false); // 初始状态为未选中
    ui->pushButton_7->setStyleSheet("QPushButton { background-color: #ffffff; }"
                              "QPushButton:checked { background-color: #808080; }");

    ui->pushButton_14->setCheckable(true); // 设置为可选中
    ui->pushButton_14->setChecked(false); // 初始状态为未选中
    ui->pushButton_14->setStyleSheet("QPushButton { background-color: #ffffff; }"
                              "QPushButton:checked { background-color: #808080; }");

    ui->pushButton_16->setCheckable(true); // 设置为可选中
    ui->pushButton_16->setChecked(false); // 初始状态为未选中
    ui->pushButton_16->setStyleSheet("QPushButton { background-color: #ffffff; }"
                              "QPushButton:checked { background-color: #808080; }");

    ui->pushButton_17->setCheckable(true); // 设置为可选中
    ui->pushButton_17->setChecked(false); // 初始状态为未选中
    ui->pushButton_17->setStyleSheet("QPushButton { background-color: #ffffff; }"
                              "QPushButton:checked { background-color: #808080; }");

    ui->pushButton_20->setCheckable(true); // 设置为可选中
    ui->pushButton_20->setChecked(false); // 初始状态为未选中
    ui->pushButton_20->setStyleSheet("QPushButton { background-color: #ffffff; }"
                              "QPushButton:checked { background-color: #808080; }");

    ui->pushButton_8->setCheckable(true); // 设置为可选中
    ui->pushButton_8->setChecked(false); // 初始状态为未选中
    ui->pushButton_8->setStyleSheet("QPushButton { background-color: #ffffff; }"
                              "QPushButton:checked { background-color: #808080; }");

    ui->pushButton_18->setCheckable(true); // 设置为可选中
    ui->pushButton_18->setChecked(false); // 初始状态为未选中
    ui->pushButton_18->setStyleSheet("QPushButton { background-color: #ffffff; }"
                              "QPushButton:checked { background-color: #808080; }");

    ui->pushButton_9->setCheckable(true); // 设置为可选中
    ui->pushButton_9->setChecked(false); // 初始状态为未选中
    ui->pushButton_9->setStyleSheet("QPushButton { background-color: #ffffff; }"
                              "QPushButton:checked { background-color: #808080; }");
}

GameType::~GameType()
{
    delete ui;
}

void GameType::setFileId(int id)
{
    fileid = id;
}




void GameType::on_pushButton_clicked()   //角色扮演
{
    if(checkState[0][0])  //判断当前是否是选中状态
    {
        if(gameTypeNum >= 10) {
            QMessageBox::warning(this,"注意","您最多只能为一款游戏添加10个标签",QMessageBox::Ok);
                    ui->pushButton->setChecked(false); // 初始状态未选中
            return;
        }
        gameTypeNum++;
        set_GameType.insert("角色扮演");
        ui->pushButton->setChecked(true); // 初始状态选中
        typeNum |= (0x01<<2);
    }
    else
    {
        gameTypeNum--;
        auto it =set_GameType.find("角色扮演");
        if(it != set_GameType.end());
        set_GameType.erase(it);
        ui->pushButton->setChecked(false); // 初始状态未选中
        typeNum &= ~(0x01<<2);
    }

    checkState[0][0] = !checkState[0][0];
}

void GameType::on_pushButton_2_clicked()    //动作射击
{
    if(checkState[0][1])  //判断当前是否是选中状态
    {
        if(gameTypeNum >= 10) {
            QMessageBox::warning(this,"注意","您最多只能为一款游戏添加10个标签",QMessageBox::Ok);
                    ui->pushButton_2->setChecked(false); // 初始状态未选中
            return;
        }
       gameTypeNum++;
       set_GameType.insert("动作射击");
        ui->pushButton_2->setChecked(true); // 初始状态选中
        typeNum |= (0x01<<3);
    }
    else
    {
        gameTypeNum--;
        auto it =set_GameType.find("动作射击");
        if(it != set_GameType.end());
        set_GameType.erase(it);
        ui->pushButton_2->setChecked(false); // 初始状态未选中
        typeNum &= ~(0x01<<3);
    }

    checkState[0][1] = !checkState[0][1];
}

void GameType::on_pushButton_3_clicked()    //模拟经营
{
    if(checkState[0][2])  //判断当前是否是选中状态
    {
        if(gameTypeNum >= 10) {
            QMessageBox::warning(this,"注意","您最多只能为一款游戏添加10个标签",QMessageBox::Ok);
                    ui->pushButton_3->setChecked(false); // 初始状态未选中
            return;
        }
        gameTypeNum++;
        set_GameType.insert("模拟经营");
        ui->pushButton_3->setChecked(true); // 初始状态选中
        typeNum |= (0x01<<4);
    }
    else
    {
        gameTypeNum--;
        auto it =set_GameType.find("模拟经营");
        if(it != set_GameType.end());
        set_GameType.erase(it);
        ui->pushButton_3->setChecked(false); // 初始状态未选中
        typeNum &= ~(0x01<<4);
    }

    checkState[0][2] = !checkState[0][2];
}

void GameType::on_pushButton_4_clicked()    //休闲益智
{
    if(checkState[0][3])  //判断当前是否是选中状态
    {
        if(gameTypeNum >= 10) {
            QMessageBox::warning(this,"注意","您最多只能为一款游戏添加10个标签",QMessageBox::Ok);
                    ui->pushButton_3->setChecked(false); // 初始状态未选中
            return;
        }
        gameTypeNum++;
        set_GameType.insert("休闲益智");
        ui->pushButton_4->setChecked(true); // 初始状态选中
        typeNum |= (0x01<<5);
    }
    else
    {
        gameTypeNum--;
        auto it =set_GameType.find("休闲益智");
        if(it != set_GameType.end());
        set_GameType.erase(it);
        ui->pushButton_3->setChecked(false); // 初始状态未选中
        typeNum &= ~(0x01<<5);
    }

    checkState[0][3] = !checkState[0][3];
}

void GameType::on_pushButton_15_clicked()   //棋牌桌游
{
    if(checkState[1][0])  //判断当前是否是选中状态
    {
        if(gameTypeNum >= 10) {
            QMessageBox::warning(this,"注意","您最多只能为一款游戏添加10个标签",QMessageBox::Ok);
            ui->pushButton_15->setChecked(false); // 状态未选中
            return;
        }
        gameTypeNum++;
        set_GameType.insert("棋牌桌游");
        ui->pushButton_15->setChecked(true); // 初始状态选中
        typeNum |= (0x01<<6);
    }
    else
    {
        gameTypeNum--;
        auto it =set_GameType.find("棋牌桌游");
        if(it != set_GameType.end());
        set_GameType.erase(it);
        ui->pushButton_15->setChecked(false); // 状态未选中
        typeNum &= ~(0x01<<6);
    }

    checkState[1][0] = !checkState[1][0];
}

void GameType::on_pushButton_7_clicked()    //音乐舞蹈
{
    if(checkState[1][1])  //判断当前是否是选中状态
    {
        if(gameTypeNum >= 10) {
            QMessageBox::warning(this,"注意","您最多只能为一款游戏添加10个标签",QMessageBox::Ok);
            ui->pushButton_7->setChecked(false); // 初始状态未选中
            return;
        }
        gameTypeNum++;
        set_GameType.insert("音乐舞蹈");
        ui->pushButton_7->setChecked(true); // 初始状态选中
        typeNum |= (0x01<<7);
    }
    else
    {
        gameTypeNum--;
        auto it =set_GameType.find("音乐舞蹈");
        if(it != set_GameType.end());
        set_GameType.erase(it);
        ui->pushButton_7->setChecked(false); // 初始状态未选中
        typeNum &= ~(0x01<<7);
    }

    checkState[1][1] = !checkState[1][1];
}

void GameType::on_pushButton_5_clicked()    //战争策略
{
    if(checkState[1][2])  //判断当前是否是选中状态
    {
        if(gameTypeNum >= 10) {
            QMessageBox::warning(this,"注意","您最多只能为一款游戏添加10个标签",QMessageBox::Ok);
            ui->pushButton_5->setChecked(false); // 初始状态未选中
            return;
        }
        gameTypeNum++;
        set_GameType.insert("战争策略");
        ui->pushButton_5->setChecked(true); // 初始状态选中
        typeNum |= (0x01<<8);
    }
    else
    {
        gameTypeNum--;
        auto it =set_GameType.find("战争策略");
        if(it != set_GameType.end());
        set_GameType.erase(it);
        ui->pushButton_5->setChecked(false); // 初始状态未选中
        typeNum &= ~(0x01<<8);
    }

    checkState[1][2] = !checkState[1][2];
}

void GameType::on_pushButton_6_clicked()    //体育竞技
{
    if(checkState[1][3])  //判断当前是否是选中状态
    {
        if(gameTypeNum >= 10) {
            QMessageBox::warning(this,"注意","您最多只能为一款游戏添加10个标签",QMessageBox::Ok);
            ui->pushButton_6->setChecked(false); // 初始状态未选中
            return;
        }
        gameTypeNum++;
        set_GameType.insert("体育竞技");
        ui->pushButton_6->setChecked(true); // 初始状态选中
        typeNum |= (0x01<<9);
    }
    else
    {
        gameTypeNum--;
        auto it =set_GameType.find("体育竞技");
        if(it != set_GameType.end());
        set_GameType.erase(it);
        ui->pushButton_6->setChecked(false); // 初始状态未选中
        typeNum &= ~(0x01<<9);
    }

    checkState[1][3] = !checkState[1][3];
}

void GameType::on_pushButton_16_clicked()   //单机
{
    if(checkState[2][0])  //判断当前是否是选中状态
    {
        if(gameTypeNum >= 10) {
            QMessageBox::warning(this,"注意","您最多只能为一款游戏添加10个标签",QMessageBox::Ok);
            ui->pushButton_16->setChecked(false); // 初始状态未选中
            return;
        }
        gameTypeNum++;
        set_GameType.insert("单机");
        ui->pushButton_16->setChecked(true); // 初始状态选中
        typeNum |= (0x01<<10);
    }
    else
    {
        gameTypeNum--;
        auto it =set_GameType.find("单人");
        if(it != set_GameType.end());
        set_GameType.erase(it);
        ui->pushButton_16->setChecked(false); // 初始状态未选中
        typeNum &= (0x01<<10);
    }

    checkState[2][0] = !checkState[2][0];
}

void GameType::on_pushButton_14_clicked()   //多人合作
{
    if(checkState[2][1])  //判断当前是否是选中状态
    {
        if(gameTypeNum >= 10) {
            QMessageBox::warning(this,"注意","您最多只能为一款游戏添加10个标签",QMessageBox::Ok);
            ui->pushButton_14->setChecked(false); // 初始状态未选中
            return;
        }
        gameTypeNum++;
        set_GameType.insert("多人合作");
        ui->pushButton_14->setChecked(true); // 初始状态选中
        typeNum |= (0x01<<11);
    }
    else
    {
        gameTypeNum--;
        auto it =set_GameType.find("多人合作");
        if(it != set_GameType.end());
        set_GameType.erase(it);
        ui->pushButton_14->setChecked(false); // 初始状态未选中
        typeNum &= (0x01<<11);
    }

    checkState[2][1] = !checkState[2][1];
}

void GameType::on_pushButton_20_clicked()   //多人对抗
{
    if(checkState[2][2])  //判断当前是否是选中状态
    {
        if(gameTypeNum >= 10) {
            QMessageBox::warning(this,"注意","您最多只能为一款游戏添加10个标签",QMessageBox::Ok);
            ui->pushButton_20->setChecked(false); // 初始状态未选中
            return;
        }
        gameTypeNum++;
        set_GameType.insert("多人对抗");
        ui->pushButton_20->setChecked(true); // 初始状态选中
        typeNum |= (0x01<<12);
    }
    else
    {
        gameTypeNum--;
        auto it =set_GameType.find("多人对抗");
        if(it != set_GameType.end());
        set_GameType.erase(it);
        ui->pushButton_20->setChecked(false); // 初始状态未选中
        typeNum &= (0x01<<12);
    }

    checkState[2][2] = !checkState[2][2];
}

void GameType::on_pushButton_17_clicked()   //线上多人
{
    if(checkState[3][0])  //判断当前是否是选中状态
    {
        if(gameTypeNum >= 10) {
            QMessageBox::warning(this,"注意","您最多只能为一款游戏添加10个标签",QMessageBox::Ok);
            ui->pushButton_17->setChecked(false); // 初始状态未选中
            return;
        }
        gameTypeNum++;
        set_GameType.insert("线上多人");
        ui->pushButton_17->setChecked(true); // 初始状态选中
        typeNum |= (0x01<<13);
    }
    else
    {
        gameTypeNum--;
        auto it =set_GameType.find("线上多人");
        if(it != set_GameType.end());
        set_GameType.erase(it);
        ui->pushButton_17->setChecked(false); // 初始状态未选中
        typeNum &= (0x01<<13);
    }

    checkState[3][0] = !checkState[3][0];
}

void GameType::on_pushButton_8_clicked()    //线下多人
{
    if(checkState[3][1])  //判断当前是否是选中状态
    {
        if(gameTypeNum >= 10) {
            QMessageBox::warning(this,"注意","您最多只能为一款游戏添加10个标签",QMessageBox::Ok);
            ui->pushButton_8->setChecked(false); // 初始状态未选中
            return;
        }
                gameTypeNum++;
                set_GameType.insert("线下多人");
        ui->pushButton_8->setChecked(true); // 初始状态选中
        typeNum |= (0x01<<14);
    }
    else
    {
        gameTypeNum--;
        auto it =set_GameType.find("线下多人");
        if(it != set_GameType.end());
        set_GameType.erase(it);
        ui->pushButton_8->setChecked(false); // 初始状态未选中
        typeNum &= ~(0x01<<14);
    }

    checkState[3][1] = !checkState[3][1];
}

void GameType::on_pushButton_18_clicked()   //男神
{
    if(checkState[4][0])  //判断当前是否是选中状态
    {
        if(gameTypeNum >= 10) {
            QMessageBox::warning(this,"注意","您最多只能为一款游戏添加10个标签",QMessageBox::Ok);
            ui->pushButton_18->setChecked(false); // 初始状态未选中
            return;
        }
                gameTypeNum++;
                set_GameType.insert("男神");
        ui->pushButton_18->setChecked(true); // 初始状态选中
        typeNum |= (0x01<<15);
    }
    else
    {
        gameTypeNum--;
        auto it =set_GameType.find("男神");
        if(it != set_GameType.end());
        set_GameType.erase(it);
        ui->pushButton_18->setChecked(false); // 初始状态未选中
        typeNum &= ~(0x01<<15);
    }

    checkState[4][0] = !checkState[4][0];
}

void GameType::on_pushButton_9_clicked()    //女神
{
    if(checkState[5][0])  //判断当前是否是选中状态
    {
        if(gameTypeNum >= 10) {
            QMessageBox::warning(this,"注意","您最多只能为一款游戏添加10个标签",QMessageBox::Ok);
            ui->pushButton_9->setChecked(false); // 初始状态未选中
            return;
        }
                gameTypeNum++;
                set_GameType.insert("女神");
        ui->pushButton_9->setChecked(true); // 初始状态选中
        typeNum |= (0x01<<16);
    }
    else
    {
        gameTypeNum--;
        auto it =set_GameType.find("女神");
        if(it != set_GameType.end());
        set_GameType.erase(it);
        ui->pushButton_9->setChecked(false); // 初始状态未选中
        typeNum &= ~(0x01<<16);
    }

    checkState[5][0] = !checkState[5][0];
}

void GameType::on_pushButton_22_clicked()   //游戏类型添加完毕
{
    //将设置的游戏类型传递出去然后退出界面
    char** buf = new char*[10];
    for(int i=0;i<10;i++)
    {
        buf[i] = new char[20];
    }
    int i=0;
    for(auto it=set_GameType.begin(); it!=set_GameType.end(); it++)
    {
        const char* str=(*it).c_str();
        memcpy(buf[i],str,(*it).size());
        i++;
    }
    emit SIG_sendGameType(buf,gameTypeNum,fileid,  typeNum);
    this->close();   //关闭本窗口

}
