#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QKeyEvent>
#include <QUdpSocket>
#include <QHostAddress>

QT_BEGIN_NAMESPACE
namespace Ui {
class MainWindow;
}
QT_END_NAMESPACE

//0.蛇的表示
//  0.1 使用链表
//1.按键处理
//2.使用定时器（构造函数）
//  2.1 关联信号槽
//  2.2 启动定时器
//  2.3 实现对应的超时函数
//3.渲染画图

//枚举型变量enum记录方向
enum enum_direct{
    dir_left,
    dir_right,
    dir_up,
    dir_down
};

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

//自定义信号
signals:
//  void signals_rank();

protected:
    //渲染绘图
    void paintEvent(QPaintEvent *event);


    //向不同方向移动的函数
    void _moveUp();
    void _moveDown();
    void _moveRight();
    void _moveLeft();

    //随机生成奖品函数
    void addNewReword();

    //按键处理
    void keyPressEvent (QKeyEvent *event);

    //游戏暂停
    bool bool_gameStra=false;

    //检测蛇头蛇身是否触碰
    bool checkContact();

    //蛇是否可以转向
    bool b_dirTime=true;

    //private:内部函数
private:
    Ui::MainWindow *ui;

    //移动方向
    int int_moveFlag = dir_right;

    //是否可以转向
    bool b_turn;

    //定时器
    QTimer *qtimer_timer;

    //蛇的链表,QRectF用来绘制矩形，是QRect的高精度版
    QList <QRectF> qlist_snake;

    //奖品
    QRectF qrectf_rewardNode;

    //单格蛇的大小,默认20像素
    double double_node=20;

    //发送对象
    QUdpSocket *sender;
    //接收对象
    QUdpSocket *receiver;


protected slots:
    //超时函数，上面的solts表示槽
    void _timeout();

    //控制转向的槽函数
    void b_dirTimeSolts();

    //控制转向的槽函数
    //void slots_network(QString _ip,QString _port);

    //接收消息槽
    //void processPendingDatagram();
};

#endif // MAINWINDOW_H
