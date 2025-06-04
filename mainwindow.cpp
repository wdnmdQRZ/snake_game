#include "mainwindow.h"
#include "gameover.h"
#include "ui_mainwindow.h"
#include <QTimer>
#include <QPainter>
#include <QDebug>
#include <QTime>
#include <QMediaPlayer>
#include <QUrl>
#include <QSoundEffect>
#include <firstwindow.h>
#include <network.h>
#include <QUdpSocket>
#include <QHostAddress>
//#include <ranklist.h>


using namespace std;

int int_score=0;


//构造函数，一开始就要用的东西
MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    //使用定时器，为蛇的移动速度
    qtimer_timer = new QTimer();
    //定时器有一个超时（timeout）信号
    //信号槽连接
    connect(qtimer_timer,SIGNAL(timeout()),this,SLOT(_timeout()));

    //设定窗口大小
    resize(800,600);

    //初始化蛇身，初始化蛇朝向，初始化奖品
    qlist_snake.append(QRectF(200,300,double_node,double_node));
    qlist_snake.append(QRectF(180,300,double_node,double_node));
    qlist_snake.append(QRectF(160,300,double_node,double_node));
    int_moveFlag=dir_right;
    qrectf_rewardNode=QRectF(600,300,double_node,double_node);

    //定义游戏初始状态
    bool_gameStra=false;
    b_turn=true;

    //设定随机数种子
    srand(QTime::currentTime().second());

    // 以下为播放音频调用方法
    // QSoundEffect *effect=new QSoundEffect;
    // effect->setSource(QUrl::fromLocalFile("/mnt/hgfs/linux-share-dir/666.wav"));
    // effect->setLoopCount(1);  //循环次数
    // effect->setVolume(0.25f); //音量  0~1之间
    // effect->play();           //播放

    //初始化分数
    int_score=0;

    //连接网络传输信号槽
    network *netw=new network();
    connect(netw,SIGNAL(sign_network(QString _ip,QString _cont)),this,SLOT(slots_network(QString _ip,QString _cont)));

    ui->label_displayScore_2->hide();
    ui->label_score_2->hide();

}

MainWindow::~MainWindow()
{
    delete ui;
}

//控制方向
void MainWindow::keyPressEvent(QKeyEvent *event){
    //初始化音频播放对象
    QSoundEffect *effect=new QSoundEffect;

    qDebug()<<"x0坐标："<<qlist_snake[0].x()<<" x1坐标："<<qlist_snake[1].x();
    qDebug()<<"y0坐标："<<qlist_snake[0].y()<<" y1坐标："<<qlist_snake[1].y();
    switch(event->key()){
    case Qt::Key_W:{
        if(qlist_snake[0].x() != qlist_snake[1].x()){
            int_moveFlag=dir_up;
            b_dirTime=false;
            //播放向上音效
            effect->setSource(QUrl::fromLocalFile(":/wav/sounds/up.wav"));
            effect->setLoopCount(1);
            effect->setVolume(1);
            effect->play();
            QTimer::singleShot(100, this, SLOT(b_dirTimeSolts()));  //每隔100毫秒触发一次，每隔100毫秒可以转向
        }
        break;
    }
    case Qt::Key_A:{
        if(qlist_snake[0].y() != qlist_snake[1].y()){
            int_moveFlag=dir_left;
            b_dirTime=false;
            //播放向左音效
            effect->setSource(QUrl::fromLocalFile(":/wav/sounds/left.wav"));
            effect->setLoopCount(1);
            effect->setVolume(1);
            effect->play();
            QTimer::singleShot(100, this, SLOT(b_dirTimeSolts()));  //每隔100毫秒触发一次，每隔100毫秒可以转向
        }
        break;
    }
    case Qt::Key_D:{
        if(qlist_snake[0].y() != qlist_snake[1].y()){
            int_moveFlag=dir_right;
            b_dirTime=false;
            //播放向右音效
            effect->setSource(QUrl::fromLocalFile(":/wav/sounds/right.wav"));
            effect->setLoopCount(1);
            effect->setVolume(1);
            effect->play();
            QTimer::singleShot(100, this, SLOT(b_dirTimeSolts()));  //每隔100毫秒触发一次，每隔100毫秒可以转向
        }
        break;
    }
    case Qt::Key_S:{
        if(qlist_snake[0].x() != qlist_snake[1].x()){
            int_moveFlag=dir_down;
            b_dirTime=false;
            //播放向下音效
            effect->setSource(QUrl::fromLocalFile(":/wav/sounds/down.wav"));
            effect->setLoopCount(1);
            effect->setVolume(1);
            effect->play();
            QTimer::singleShot(100, this, SLOT(b_dirTimeSolts()));  //每隔100毫秒触发一次，每隔100毫秒可以转向
        }
        break;
    }
    case Qt::Key_Space:{
        qDebug()<<"空格键按下";
        if(bool_gameStra==false){
            bool_gameStra=true;
            //当游戏开启，启动定时器
            qtimer_timer->start(100);
            qDebug()<<"定时器启动";
            //清除中央文字
            ui->label_star->setText(" ");
        }
        else{
            bool_gameStra=false;
            //当游戏暂停，关闭定时器
            qtimer_timer->stop();
            qDebug()<<"定时器关闭";
            //显示暂停文字
            ui->label_star->setText("游戏已暂停");
        }
        break;
    }
    default:{
        break;
    }
    }
}

//调用mainwindow头文件里的 timeout() 函数
void MainWindow::_timeout(){
    //初始化音频播放对象
    QSoundEffect *effect=new QSoundEffect;

    //显示分数
    ui->label_displayScore->setNum(int_score);//用Qlable输出分数

    int int_eat=0;
    //判断蛇和苹果有没有重合,用intersects方法，A.intersects(B)
    if(qlist_snake[0].intersects(qrectf_rewardNode)){
        //如果吃了苹果，少删除一次
        int_score++;
        int_eat=1;

        //播放吃的声音
        effect->setSource(QUrl::fromLocalFile(":/wav/sounds/eat.wav"));
        effect->setLoopCount(1);
        effect->setVolume(1);
        effect->play();

        addNewReword();
    }
    switch(int_moveFlag){
    case dir_up:{
        //向上移动
        _moveUp();
        qDebug()<<"执行向上移动指令";
        if(int_eat==1){
            goto l1;
        }
        break;
    }
    case dir_down:{
        //向下移动
        _moveDown();
        qDebug()<<"执行向下移动指令";
        if(int_eat==1){
            goto l1;
        }
        break;
    }
    case dir_right:{
        //向右移动
        _moveRight();
        qDebug()<<"执行向右移动指令";
        if(int_eat==1){
            goto l1;
        }
        break;
    }
    case dir_left:{
        //向左移动
        _moveLeft();
        qDebug()<<"执行向左移动指令";
        if(int_eat==1){
            goto l1;
        }
        break;
    }
    }
    //删除最后一个方块
    qlist_snake.removeLast();

    l1:
    //重新绘制
    update();
}


//向上移动函数
void MainWindow::_moveUp(){
    //左上角右下角坐标
    QPointF qpointf_leftTop;
    QPointF qpointf_rightBottom;

    //如果到达最顶端，在尾部加一个
    if(qlist_snake[0].y()-double_node<0){
        //this->height()为窗口高度
        qpointf_leftTop=QPoint(qlist_snake[0].x(),this->height()-double_node);
        qpointf_rightBottom=QPoint(qlist_snake[0].x()+double_node,this->height());
    }
    //正常情况
    else{
        qpointf_leftTop=QPointF(qlist_snake[0].x(),qlist_snake[0].y()-double_node);
        qpointf_rightBottom=QPointF(qlist_snake[0].topRight());
    }

    //链表的第一个位置加入一个QRectF()数据
    qlist_snake.insert(0,QRectF(qpointf_leftTop,qpointf_rightBottom));
}

//向下移动函数
void MainWindow::_moveDown(){
    //左上角右下角坐标
    QPointF qpointf_leftTop;
    QPointF qpointf_rightBottom;

    //如果到达最底，在尾部加一个
    if(qlist_snake[0].y()+double_node>this->height()-1){
        //this->height()为窗口高度
        qpointf_leftTop=QPoint(qlist_snake[0].x(),0);
        qpointf_rightBottom=QPoint(qlist_snake[0].x()+double_node,double_node);
    }
    //正常情况
    else{
        qpointf_leftTop=QPointF(qlist_snake[0].bottomLeft());
        qpointf_rightBottom=QPointF(qlist_snake[0].x()+double_node,qlist_snake[0].y()+double_node+double_node);
    }

    //链表的第一个位置加入一个QRectF()数据
    qlist_snake.insert(0,QRectF(qpointf_leftTop,qpointf_rightBottom));
}

//向左移动函数
void MainWindow::_moveLeft(){
    //左上角右下角坐标
    QPointF qpointf_leftTop;
    QPointF qpointf_rightBottom;

    //如果到达最左边，在尾部加一个
    if(qlist_snake[0].x()-double_node<0){
        //this->height()为窗口高度
        qpointf_leftTop=QPoint(this->width()-double_node,qlist_snake[0].y());
        qpointf_rightBottom=QPoint(this->width(),qlist_snake[0].y()+double_node);
    }
    //正常情况
    else{
        qpointf_leftTop=QPointF(qlist_snake[0].x()-double_node,qlist_snake[0].y());
        qpointf_rightBottom=QPointF(qlist_snake[0].bottomLeft());
    }

    //链表的第一个位置加入一个QRectF()数据
    qlist_snake.insert(0,QRectF(qpointf_leftTop,qpointf_rightBottom));
}

//向右移动函数
void MainWindow::_moveRight(){
    //左上角右下角坐标
    QPointF qpointf_leftTop;
    QPointF qpointf_rightBottom;

    //如果到达最右边，在尾部加一个
    if(qlist_snake[0].x()+double_node>this->width()-1){
        //this->height()为窗口高度
        qpointf_leftTop=QPoint(0,qlist_snake[0].y());
        qpointf_rightBottom=QPoint(double_node,qlist_snake[0].y()+double_node);
    }
    //正常情况
    else{
        qpointf_leftTop=QPointF(qlist_snake[0].topRight());
        qpointf_rightBottom=QPointF(qlist_snake[0].x()+double_node+double_node,qlist_snake[0].y()+double_node);
    }

    //链表的第一个位置加入一个QRectF()数据
    qlist_snake.insert(0,QRectF(qpointf_leftTop,qpointf_rightBottom));
}

//绘制渲染
void MainWindow::paintEvent(QPaintEvent *event){
    //初始化音频播放对象
    QSoundEffect *effect=new QSoundEffect;

    //定义画家，画笔，画刷
    QPainter painter(this);
    QPen pen;
    QBrush brush;

    //背景图片，使用资源文件保存图片
    QPixmap map;
    map.load(":/map/XP.jpg");
    painter.drawPixmap(0,0,800,600,map);

    //画蛇
    pen.setColor(Qt::black);    //画笔颜色
    brush.setColor(Qt::green);  //刷子颜色
    brush.setStyle(Qt::SolidPattern);   //实心填充样式
    painter.setPen(pen);        //画笔给画家
    painter.setBrush(brush);    //画刷给画家

    //遍历每一个蛇的点，并绘制这些方块
    for(int i=0;i<qlist_snake.length();i++){
        painter.drawRect(qlist_snake[i]);//以方块方式画蛇
    }

    //画奖品
    pen.setColor(Qt::black);    //画笔颜色
    brush.setColor(Qt::red);    //刷子颜色
    brush.setStyle(Qt::SolidPattern);   //实心填充样式
    painter.setPen(pen);        //画笔给画家
    painter.setBrush(brush);    //画刷给画家
    painter.drawEllipse(qrectf_rewardNode);//以圆方式画奖品

    //检查蛇是否触碰自己
    if(checkContact()){
        qtimer_timer->stop();
        qDebug()<<"游戏结束";

//      //传递信号槽，把分数传给排行榜窗口
//          ranklist *ranklis=new ranklist();
//          connect(this,SIGNAL(signals_rank()),ranklis,SLOT(slot_rank()));



        this->close();
        gameover *_over=new gameover();
        _over->show();
    }
}

//随机生成食物
void MainWindow::addNewReword(){
    qrectf_rewardNode=QRectF(rand()%(this->width()/20)*20,rand()%(this->height()/20)*20,double_node,double_node);
}

//检测蛇是否和自己碰撞
bool MainWindow::checkContact(){
    for(int i=1;i<qlist_snake.length();i++){
        if(qlist_snake[0]==qlist_snake[i]){
            qlist_snake[0];
            return true;
        }
    }
    return false;
}

void MainWindow::b_dirTimeSolts(){
    b_dirTime=true;
}

//void MainWindow::slots_network(QString _ip,QString _port){
    // ui->label_score_2->show();
    // ui->label_displayScore_2->show();

    // //string转换ip和cont
    // QHostAddress host = QHostAddress (_ip);
    // quint16 port = _port.toShort();

    // QByteArray datagram="cont";

    // //创建一个新的QUdpSocket实例，发送
    // sender = new QUdpSocket(this);

    // //创建一个新的QUdpSocket实例，接收
    // receiver = new QUdpSocket(this);
    // receiver->bind(port,(QUdpSocket::ShareAddress));
    // connect(receiver,SIGNAL(readyRead()),this,SLOT(processPendingDatagram()));

    // while(1){
    //     int a=sender->writeDatagram(datagram.data(),datagram.size(),host, port);
    //     if(a==1){
    //         break;
    //     }
    // }

//}
