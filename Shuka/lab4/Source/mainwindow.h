#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QTextStream>
#include <QFile>
#include <QFileDialog>
#include <QMessageBox>
#include <QDebug>
#include <QDir>
#include <QString>
#include <string>
#include "mybinarytree.h"


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
    void on_readFromFile_radioButton_clicked();
    void on_readFromWindow_radioButton_clicked();

    bool readCharTree(MyBinaryTree<char>* charTree);
    bool isCorrectStr(const std::string& str);

    void on_test_pushButton_clicked();
    void on_do_pushButton_clicked();

private:
    Ui::MainWindow *ui;
    QTextStream* in;
    QFile* file;
    QDir* dir;
    MyBinaryTree<char>* charTree;
};

#endif // MAINWINDOW_H
