#include "ranklist.h"
#include "ui_ranklist.h"

ranklist::ranklist(QWidget *parent)
    : QDialog(parent)
    , ui(new Ui::ranklist)
{
    ui->setupUi(this);
}

ranklist::~ranklist()
{
    delete ui;
}
