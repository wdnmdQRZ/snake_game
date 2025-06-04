#ifndef RANKLIST_H
#define RANKLIST_H

#include <QDialog>

namespace Ui {
class ranklist;
}

class ranklist : public QDialog
{
    Q_OBJECT

public:
    explicit ranklist(QWidget *parent = nullptr);
    ~ranklist();

private slots:
//  void slot_rank();

private:
    Ui::ranklist *ui;
};

#endif // RANKLIST_H
