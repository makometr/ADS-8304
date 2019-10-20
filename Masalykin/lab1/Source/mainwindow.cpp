#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    //file = new QFile;
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::on_pushButton_2_clicked()
{
    QApplication::quit();
}

bool MainWindow::is_brackets(std::string inp, unsigned int i, int br_cntr, bool flag){
    if(i == inp.length() - 1){
        if(inp[i] == 'A'){
            return true;
        }
        else{
            return false;
        }
    }
    if(inp == "AA")
        return false;
    if(inp[i] == 'A' && i != inp.length() -1 && flag)
        return false;
    if(!flag){
        if(inp[i] == '('){
            i++;
            br_cntr++;
            if(inp[i]  == 'B'){
                i++;
                return is_brackets(inp, i, br_cntr, flag);
            }
            else{
            return false;
            }
        }
        else if(inp[i] == 'A'){
            i++;
            flag = true;
            return is_brackets(inp, i, br_cntr, flag);
        }
                else{
            return false;
        }

    }
    else{
        if(inp[i] == ')'){
            if(br_cntr > 0){
                i++;
                return is_brackets(inp, i, br_cntr -1, flag);
            }
            else{
                return false;
            }
        }
        if(inp[i] != 'A'){
            flag = false;
            return is_brackets(inp, i, br_cntr, flag);
        }
    }
    return false;
}

void MainWindow::on_pushButton_clicked()
{
    if(test(QApplication::applicationDirPath() + "/Tests/true_test.txt", true) &&
            test(QApplication::applicationDirPath() + "/Tests/false_test.txt", false))
        QMessageBox::information(this, "Test", "Tests passed");
    else
        QMessageBox::warning(this, "Test", "Tests not passed");
}

void MainWindow::on_pushButton_3_clicked()
{
    res = ui->lineEdit->text().toStdString();
    if(is_brackets(res, 0, 0, false)){
        QMessageBox::information(this, "Result", "EXPRESSION");
    }
    else{
        QMessageBox::warning(this, "Result", "NOT EXPRESSION");
    }
}

bool MainWindow::test(QString way, bool expected_result){
    QFile file(way);
    file.open(QIODevice::ReadOnly);
    while(!file.atEnd())
        {
            if(is_brackets(file.readLine().toStdString(), 0, 0, false) != expected_result)
                return false;
        }
    return true;
}
