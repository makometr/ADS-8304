#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::on_pushButton_2_clicked()
{
    QApplication::quit();
}

bool MainWindow::is_brackets(std::string inp, unsigned long long i, int br_cntr, bool flag){
    if(i == inp.length() - 1){
        if(inp[i] == 'A'){
            return true;
        }
        else{
            return false;
        }
    }
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
    if(is_brackets("A", 0, 0 ,false) == true){
         if (is_brackets("(B(B(B(BA))))A", 0, 0 ,false) == true) {
             if (is_brackets("", 0, 0 ,false) == false){
                 if(is_brackets("AAA", 0, 0 ,false) == false){
                     if(is_brackets("()", 0, 0 ,false) == false){
                        if(is_brackets("(B(B(B(B(B(BA))))))(B(B(BA)))A", 0, 0 ,false) == true)
                        QMessageBox::information(this, "Result", "Tests passed");
                     }
                 }
             }
         }
    }
}

void MainWindow::on_pushButton_3_clicked()
{
    res = ui->lineEdit->text().toStdString();
    if(res == "AA"){
        QMessageBox::warning(this, "Result", "NOT EXPRESSION");
        return;
    }
    if(is_brackets(res, 0, 0, false)){
        QMessageBox::information(this, "Result", "EXPRESSION");
    }
    else{
        QMessageBox::warning(this, "Result", "NOT EXPRESSION");
    }
}
