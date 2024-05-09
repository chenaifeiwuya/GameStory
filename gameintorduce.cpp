#include "gameintorduce.h"
#include "ui_gameintorduce.h"

GameIntorduce::GameIntorduce(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::GameIntorduce)
{
    ui->setupUi(this);
}

GameIntorduce::~GameIntorduce()
{
    delete ui;
}

void GameIntorduce::setGamePath(QString path)
{
    this->path = path;
}
