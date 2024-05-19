#include "cmind.h"
#include "ui_cmind.h"

CMind::CMind(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::CMind),
    mindRes(0),
    data(0x01)
{
    ui->setupUi(this);
    lstStr.push_back("1．当你遇到新朋友时，你\nA．说话的时间与聆听的时间相当。\nB．聆听的时间会比说话的时间多。");
    lstStr.push_back("2．下列哪一种是你的一般生活取向\nA．只管做吧。\nB．找出多种不同选择。");
    lstStr.push_back("3．你喜欢自己的哪种性格？\nA．冷静而理性。\nB．热情而体谅。");
    lstStr.push_back("4．你擅长\nA．在有需要时间时同时协调进行多项工作。\nB．专注在某一项工作上，直至把它完成为止。");
    lstStr.push_back("5．你参与社交聚会时\nA．总是能认识新朋友。\nB．只跟几个亲密挚友呆在一起。");
    lstStr.push_back("6．当你尝试了解某些事情时，一般你会\nA．先要了解细节。\nB．先了解整体情况，细节容后再谈。");
    lstStr.push_back("7．你对下列哪方面较感兴趣？\nA．知道别人的想法。\nB．知道别人的感受。");
    lstStr.push_back("8．你较喜欢下列哪个工作？\nA．能让你迅速和即时做出反应。\n B．能让你定出目标，然后逐步达成目标的工作。");
    lstStr.push_back("9. A．当我与友人尽兴后，我会感到精力充沛，并会继续追求这种欢娱。\nB．当我与友人尽兴后，我会感到疲累，觉得需要一些空间。");
    lstStr.push_back("10．A．我较有兴趣知道别人的经历，例如他们做过什么？认识什么人？\nB．我较有兴趣知道别人的计划和梦想，例如他们会往哪里去？憧憬什么？");
    lstStr.push_back("11．A．我擅长订出一些可行的计划。\n B．我擅长促成别人同意一些计划，并衷力合作。");
    lstStr.push_back("12．A．我会突然尝试做某些事，看看会有什么事情发生。\nB．我尝试做任何事前，都想事先知道可能有什么事情发生。");
    lstStr.push_back("13．A．我经常边说话，边思考。\n B．我在说话前，通常会思考要说的话。");
    lstStr.push_back("14．A．四周的实际环境对我很重要，而且会影响我的感受。\nB．如果我喜欢所做的事情，气氛对我而言并不是那么重要。");
    lstStr.push_back("15．A．我喜欢分析，心思缜密。\nB．我对人感兴趣，关心他们所发生的事。");
    lstStr.push_back("16．A．即使已出计划，我也喜欢探讨其他新的方案。\n B．一旦定出计划，我便希望能依计行事。");
    lstStr.push_back("17．A．认识我的人，一般都知道什么对我来说是重要的。B．除了我感觉亲近的人，我不会对人说出什么对我来说是重要的。");
    lstStr.push_back("18．A．如果我喜欢某种活动，我会经常进行这种活动。B．我一旦熟悉某种活动后，便希望转而尝试其它新的活动。");
    lstStr.push_back("19．A．当我作决定的时候，我更多地考虑正反两面的观点，并且会推理与质证。\nB．当我作决定的时候，我会更多地了解其他人的想法，并希望能够达成共识。");
    lstStr.push_back("20．A．当我专注做某件事情时，需要不时停下来休息。\nB．当我专注做某件事情时，不希望受到任何干扰。");
    lstStr.push_back("21．A．我独处太久，便会感到不安。B．若没有足够的自处时间，我便会感到烦躁不安。");
    lstStr.push_back("22．A．我对一些没有实际用途的意念不感兴趣。\nB．我喜欢意念本身，并享受想象意念的过程。");
    lstStr.push_back("23．A．当进行谈判时，我依靠自己的知识和技巧。\nB．当进行谈判时，我会拉拢其他人至同一阵线。");

    ui->label_edit->setText(lstStr.front());
    lstStr.pop_front();

}

CMind::~CMind()
{
    delete ui;
}

#include <QPainter>
void CMind::paintEvent(QPaintEvent *ev)
{
    QPainter painter(this);
    painter.setOpacity(0.5);    //设置绘制时透明度为50%
    painter.drawPixmap(rect(),QPixmap(":/images/myimages/images/ysLH.png"),QRect());
}

void CMind::on_pb_A_clicked()
{
    //切换当前显示的题目
    if(!lstStr.empty()){
        ui->label_edit->setText(lstStr.front());
        lstStr.pop_front();
        //0代表答案为A，1代表答案为B
        data << 1;
    }
    else
    {
        //将得到的信息发送给服务器
        emit SIG_sendUserMind(mindRes);
        this->close();
    }


}



void CMind::on_pb_B_clicked()
{
    //切换当前显示的题目
    if(!lstStr.empty()){
        ui->label_edit->setText(lstStr.front());
        lstStr.pop_front();
        //0代表答案为A，1代表答案为B
        data << 1;
        mindRes |= data;
    }
    else{
        //将得到的信息发送给服务器
        emit SIG_sendUserMind(mindRes);
        this->close();
    }

}
