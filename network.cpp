#include "network.h"
#include "ui_network.h"


network::network(QWidget *parent)
    : QDialog(parent)
    , ui(new Ui::network)
{
    ui->setupUi(this);
}

network::~network()
{
    delete ui;
}


void network::on_pushButton_connect_clicked()
{
    //发送数据
    emit sign_network(ui->lineEdit_ip->text(),ui->lineEdit_cont->text());


}

