#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QDebug>
#include <vector>
#include <string>
#include <QStringList>
#include <QMessageBox>
#include <QDir>
#include <QTextStream>
#include <QFile>
#include <QFileDialog>

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
    void on_chek_pushButton_clicked();

    //Функция вычисления пути
    static void PavingTheRoute(size_t i, std::vector<std::vector<size_t>>& roads, std::vector<bool>& visited, size_t depth = 0);

    void on_readFromFile_radioButton_clicked();

    void on_readFromWindow_radioButton_clicked();

    void on_test_pushButton_clicked();

private:
    Ui::MainWindow *ui;
    QDir* dir;
    QTextStream* in;
    QFile* file;
};

#endif // MAINWINDOW_H
