#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QTextStream>
#include <QFile>
#include <QFileDialog>
#include <QMessageBox>
#include <QDebug>
#include <QString>
#include <QDir>
#include <QStringList>
#include <QFileSystemModel>
#include <string>
#include "mylist.h"

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = nullptr);
    ~MainWindow();
    void create_new_list(MyList::MyListP inp_list, std::list<char>* new_list, int depth);
    void print_list(std::list<char> list);

private slots:
    void on_create_pushButton_clicked();

    void on_test_pushButton_clicked();

private:
    Ui::MainWindow *ui;
    QFile* file;
    QDir* dir;
};

#endif // MAINWINDOW_H
