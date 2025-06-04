#include "firstwindow.h"
#include "ui_firstwindow.h"
#include <QPainter>
#include <mainwindow.h>
#include <QDebug>
#include <gamehelp.h>
#include <QMediaPlayer>
#include <QUrl>
#include <QSoundEffect>
#include <network.h>
#include <ranklist.h>

double double_music=0.1;
//初始化音频播放对象
QSoundEffect *firstwav=new QSoundEffect;

firstwindow::firstwindow(QWidget *parent)
    : QDialog(parent)
    , ui(new Ui::firstwindow)
{
    ui->setupUi(this);

    //播放初始音乐
    firstwav->setSource(QUrl::fromLocalFile(":/wav/sounds/8bit.wav"));
    firstwav->setLoopCount(1000);
    firstwav->setVolume(double_music);
    firstwav->play();
}

firstwindow::~firstwindow()
{
    delete ui;
}

void firstwindow::paintEvent(QPaintEvent *event){
    //定义画家，画笔，画刷
    QPainter painter(this);

    //背景图片，使用资源文件保存图片
    QPixmap first;
    first.load(":/map/first.jpg");
    painter.drawPixmap(0,0,800,600,first);
    qDebug()<<"画图";
}

void firstwindow::on_pushButton_pve_clicked()
{
    MainWindow *mainwindow=new MainWindow();
    mainwindow->show();
    this->close();
}


void firstwindow::on_pushButton_help_clicked()
{
    gamehelp *gameh=new gamehelp();
    gameh->show();
}



void firstwindow::on_pushButton_pvp_clicked()
{
    network *netwo=new network();
    netwo->show();
}


void firstwindow::on_pushButton_look_clicked()
{
    ranklist *ranklis=new ranklist();
    ranklis->show();
}

