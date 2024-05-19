#ifndef CMIND_H
#define CMIND_H

#include <QWidget>

namespace Ui {
class CMind;
}

class CMind : public QWidget
{
    Q_OBJECT

public:
    explicit CMind(QWidget *parent = 0);
    ~CMind();
    void paintEvent(QPaintEvent* ev)override;

private slots:
    void on_pb_A_clicked();

    void on_pb_B_clicked();

signals:
    void SIG_sendUserMind(int mind);

private:
    Ui::CMind *ui;
    QStringList lstStr;
    int mindRes;
    int data;
};

#endif // CMIND_H
