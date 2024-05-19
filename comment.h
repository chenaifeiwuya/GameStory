#ifndef COMMENT_H
#define COMMENT_H

#include <QWidget>

namespace Ui {
class comment;
}

class comment : public QWidget
{
    Q_OBJECT

public:
    explicit comment(QWidget *parent = 0);
    ~comment();
    void setComment(QString name, QString commentText, int point);
    void setDream(QString name,QString dreamText);
    void paintEvent(QPaintEvent* ev)override;
    void setPixmapPath(int id);   //一共有ys1 - 9张图片可选

private:
    Ui::comment *ui;
    QString pixmappath;
};

#endif // COMMENT_H
