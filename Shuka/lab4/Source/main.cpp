#include "mainwindow.h"
#include <QApplication>

//var #1-v


int main(int argc, char *argv[])
{
    QApplication app(argc, argv);

    MainWindow window;
    window.setWindowTitle("Lr#4 var #1-v");
    window.show();

    return app.exec();
}
