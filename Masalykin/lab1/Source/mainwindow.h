#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QDebug>
#include <QTextStream>
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
    //void on_lineEdit_editingFinished();

    void on_pushButton_2_clicked();

    void on_pushButton_clicked();

    void on_pushButton_3_clicked();

public:
    bool is_brackets(std::string inp, unsigned long long i, int br_cntr, bool flag);

private:
    Ui::MainWindow *ui;
    QTextStream *inp;
    std::string res;
};

#endif // MAINWINDOW_H
