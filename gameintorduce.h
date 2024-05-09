#ifndef GAMEINTORDUCE_H
#define GAMEINTORDUCE_H

#include <QWidget>

namespace Ui {
class GameIntorduce;
}

class GameIntorduce : public QWidget
{
    Q_OBJECT

public:
    explicit GameIntorduce(QWidget *parent = 0);
    ~GameIntorduce();
    void setGamePath(QString path);
private:
    Ui::GameIntorduce *ui;
    QString path;
};

#endif // GAMEINTORDUCE_H
