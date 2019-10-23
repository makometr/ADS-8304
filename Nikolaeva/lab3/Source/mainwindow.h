#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#define QT_NO_DEBUG_OUTPUT

#include <QMainWindow>
#include <QDebug>
#include <string>
#include <QString>
#include <QMessageBox>
#include <QTextStream>
#include <QFile>
#include <QFileDialog>
#include "stack.h"

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
    void on_prefixToInfix_pushButton_clicked();
    void on_readFromFile_radioButton_clicked();
    void on_readFromWindow_radioButton_clicked();

public slots:
    static std::string prefixToInfix(const std::string& expression);
    static bool isSign(const char ch);
    static bool isAlpha(const char ch);
    static bool isDigit(const char ch);

private:
    Ui::MainWindow *ui;
    QTextStream* in;
    QFile* file;
};

#endif // MAINWINDOW_H
