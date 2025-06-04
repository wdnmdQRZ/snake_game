#ifndef FIRSTWINDOW_H
#define FIRSTWINDOW_H

#include <QDialog>

namespace Ui {
class firstwindow;
}

class firstwindow : public QDialog
{
    Q_OBJECT

public:
    explicit firstwindow(QWidget *parent = nullptr);
    ~firstwindow();

    void paintEvent(QPaintEvent *event);

private slots:
    void on_pushButton_pve_clicked();

    void on_pushButton_help_clicked();

    void on_pushButton_pvp_clicked();

    void on_pushButton_look_clicked();

private:
    Ui::firstwindow *ui;
};

#endif // FIRSTWINDOW_H
