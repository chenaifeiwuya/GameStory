#ifndef CSTARPOINT_H
#define CSTARPOINT_H

#include <QWidget>

namespace Ui {
class CStarPoint;
}

class CStarPoint : public QWidget
{
    Q_OBJECT

public:
    explicit CStarPoint(QWidget *parent = 0);
    ~CStarPoint();
    void paintEvent(QPaintEvent* ev)override;
signals:
    void SIG_GamePoint(int point);   //游戏分数

private slots:
    void on_pushButton_6_clicked();

    void on_pushButton_clicked();

    void on_pushButton_2_clicked();

    void on_pushButton_3_clicked();

    void on_pushButton_4_clicked();

    void on_pushButton_5_clicked();

private:
    Ui::CStarPoint *ui;
    int point;
};

#endif // CSTARPOINT_H
