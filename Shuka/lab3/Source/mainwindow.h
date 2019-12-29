#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#define QT_NO_DEBUG_OUTPUT

#include <QMainWindow>
#include <QTextStream>
#include <QFile>
#include <QFileDialog>
#include <QMessageBox>
#include <QDebug>
#include <QString>
#include <QDir>
#include <QStringList>
#include <string>
#include "mystack.h"


namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

public slots:
    static std::string toInfix(MyStack* stack, const std::string& expression);
    static bool isSign(const char ch);
    static bool isAlpha(const char ch);
    static bool isDigit(const char ch);


private slots:
    void on_readFile_radioButton_clicked();

    void on_readLineEdit_radioButton_clicked();

    void on_readPostfix_radioButton_clicked();

    void on_toInfix_pushButton_clicked();

private:
    Ui::MainWindow *ui;
    QTextStream* in;
    QFile* file;
    QDir* dir;
};

#endif // MAINWINDOW_H
