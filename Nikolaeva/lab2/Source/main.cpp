#include "mainwindow.h"
#include <QApplication>

//var #14

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    MainWindow w;
    w.setWindowTitle("lab 2 var #14");
    w.show();

    return a.exec();
}
