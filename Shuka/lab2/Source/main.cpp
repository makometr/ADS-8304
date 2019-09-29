#include "mainwindow.h"
#include <QApplication>


//var #15


int main(int argc, char *argv[])
{
    QApplication app(argc, argv);

    MainWindow window;
    window.setWindowTitle("Lr#2 var#15");
    window.show();

    return app.exec();
}
