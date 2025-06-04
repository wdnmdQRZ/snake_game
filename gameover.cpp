#include "gameover.h"
#include "ui_gameover.h"
#include <QMediaPlayer>
#include <QUrl>
#include <QSoundEffect>
#include <mainwindow.h>
#include <firstwindow.h>

gameover::gameover(QWidget *parent)
    : QDialog(parent)
    , ui(new Ui::gameover)
{
    ui->setupUi(this);
    //初始化音频播放对象
    QSoundEffect *effect=new QSoundEffect;
    effect->setSource(QUrl::fromLocalFile(":/wav/sounds/died.wav"));
    effect->setLoopCount(1);
    effect->setVolume(1);
    effect->play();
}

gameover::~gameover()
{
    delete ui;
}

void gameover::on_pushButton_clicked()
{
    MainWindow *_main=new MainWindow();
    _main->show();
    this->close();
}


void gameover::on_pushButton_2_clicked()
{
    firstwindow *first=new firstwindow();
    first->show();
    this->close();
}

