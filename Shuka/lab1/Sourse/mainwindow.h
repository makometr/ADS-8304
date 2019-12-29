#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QDebug>
#include <QString>
#include <QFile>
#include <QMessageBox>
#include <QFileDialog>
#include <QTextStream>


namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private:
    bool isSign(const char ch) const;

    bool isLetter(const char ch) const;

    bool isExpression(std::string::iterator& pos,
                      size_t depth = 0) const;

private slots:
    void on_check_pushButton_clicked();

    void on_checkBox_clicked();

public slots:
    void test();

private:
    Ui::MainWindow *ui;
    std::string result;
    QTextStream* in;
    QFile* file;

};

#endif // MAINWINDOW_H
