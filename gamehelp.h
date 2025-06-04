#ifndef GAMEHELP_H
#define GAMEHELP_H

#include <QDialog>

namespace Ui {
class gamehelp;
}

class gamehelp : public QDialog
{
    Q_OBJECT

public:
    explicit gamehelp(QWidget *parent = nullptr);
    ~gamehelp();

private slots:
    void on_pushButton_clicked();

private:
    Ui::gamehelp *ui;
};

#endif // GAMEHELP_H
