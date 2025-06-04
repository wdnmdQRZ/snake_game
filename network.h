#ifndef NETWORK_H
#define NETWORK_H

#include <QDialog>

namespace Ui {
class network;
}

class network : public QDialog
{
    Q_OBJECT

public:
    explicit network(QWidget *parent = nullptr);

    ~network();


//自定义信号
signals:
    //信号没有返回值，可以有参数,信号函数不需要定义，只需要声明
    void sign_network(QString _ip,QString _port);
    //自定义槽函数

private slots:
    void on_pushButton_connect_clicked();

private:
    Ui::network *ui;
};

#endif // NETWORK_H
