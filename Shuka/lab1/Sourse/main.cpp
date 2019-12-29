#include "mainwindow.h"
#include <QApplication>


//var #6

int main(int argc, char *argv[]) {
    setlocale(LC_ALL, "Russian");

    QApplication a(argc, argv);

    MainWindow window;
    if (argc == 2 && strcmp(argv[1], "--test") == 0) {
        window.test();
        return 0;
    }

    window.setWindowTitle("Lab_1. Var. #6");
    window.show();

    return a.exec();
}
