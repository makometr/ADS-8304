#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QDir>
#include <QFile>
#include <QString>
#include <QMessageBox>
#include <iostream>
#include <string>

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private slots:

    void on_pushButton_2_clicked();

    void on_pushButton_clicked();

    void on_pushButton_3_clicked();

public:
    bool is_brackets(std::string inp, unsigned int i, int br_cntr, bool flag);

    bool test(QString way, bool expected_result);

private:
    Ui::MainWindow *ui;
    std::string res;
    QDir *dir;
    //QFile* file;
};

#endif // MAINWINDOW_H
