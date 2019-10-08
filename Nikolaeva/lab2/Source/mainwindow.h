#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QDebug>
#include <string>
#include <QString>
#include <QMessageBox>
#include <QTextStream>
#include <QFile>
#include <QFileDialog>
#include "hierarchicallist.h"


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
    void on_reverse_pushButton_clicked();
    void on_readFromFile_radioButton_clicked();
    void on_readFromWindow_radioButton_clicked();

private:
    Ui::MainWindow *ui;
    QTextStream* in;
    QFile* file;
};

#endif // MAINWINDOW_H
