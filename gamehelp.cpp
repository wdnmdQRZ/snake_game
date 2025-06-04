#include "gamehelp.h"
#include "ui_gamehelp.h"
#include <firstwindow.h>

gamehelp::gamehelp(QWidget *parent)
    : QDialog(parent)
    , ui(new Ui::gamehelp)
{
    ui->setupUi(this);
}

gamehelp::~gamehelp()
{
    delete ui;
}

void gamehelp::on_pushButton_clicked()
{
    this->close();
}


