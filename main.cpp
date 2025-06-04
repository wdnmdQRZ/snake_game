#include "mainwindow.h"
#include <firstwindow.h>
#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    MainWindow w;
    firstwindow f;
    f.show();
    return a.exec();
}
