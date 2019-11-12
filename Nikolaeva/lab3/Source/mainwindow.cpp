#include "mainwindow.h"
#include "ui_mainwindow.h"


MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    in = new QTextStream;
    file = new QFile;

    ui->setupUi(this);
    ui->readFromWindow_radioButton->setChecked(true);
}


MainWindow::~MainWindow()
{
    delete file;
    delete in;
    delete ui;
}


void MainWindow::on_readFromFile_radioButton_clicked()
{
    file->close();

    ui->textLabel_0->setEnabled(false);
    ui->input_lineEdit->setEnabled(false);
    ui->input_lineEdit->clear();

    QString fileName = QFileDialog::getOpenFileName(this, "Open file", "", "*.txt");
    file->setFileName(fileName);
    file->open(QFile::ReadOnly | QFile::Text);
    in->setDevice(file);

    if (fileName != "")
        ui->fileName_textLabel->setText(fileName);
    else
        ui->fileName_textLabel->setText("none");
}


void MainWindow::on_readFromWindow_radioButton_clicked()
{
    file->close();

    ui->textLabel_0->setEnabled(true);
    ui->input_lineEdit->setEnabled(true);
    ui->input_lineEdit->clear();
    ui->fileName_textLabel->setText("none");
}


void MainWindow::on_prefixToInfix_pushButton_clicked()
{
    std::string tmpStr;

    if (ui->readFromWindow_radioButton->isChecked()) {
        tmpStr= ui->input_lineEdit->text().toStdString();
    }
    else {
        tmpStr = in->readLine().toStdString();
    }

    std::string result = MainWindow::prefixToInfix(tmpStr);

    if (result != "") {
        qDebug() << "Выражение в инфиксной форме: " << result.c_str();
        QMessageBox::information(this, "Result", result.c_str());
    }
    else {
        qDebug() << "Введенное выражение некорректно";
        QMessageBox::warning(this, "Result", "Введенное выражение некорректно");
    }

    ui->input_lineEdit->clear();
    qDebug() << "End";
}


bool MainWindow::isDigit(const char ch)
{
    return (ch >= '0' && ch <= '9');
}


bool MainWindow::isAlpha(const char ch)
{
    return ((ch >= 'A' && ch <= 'Z') || (ch >= 'a' && ch <= 'z'));

}


bool MainWindow::isOperator(const char ch)
{
    return (ch == '+' || ch == '-' || ch == '*' || ch == '^');
}


std::string MainWindow::prefixToInfix(const std::string &expression)
{
    Stack stack;
    std::string tmpStr;
    for (auto i = expression.crbegin(); i < expression.crend(); ++i) {
        char elem = *i;
        if (elem == ' ') {
            continue;
        }
        if (isDigit(elem) || isAlpha(elem) ) {
            bool isDigitElem = isDigit(elem);
            while (elem != ' ' && i != expression.crend()) {
                bool isAlphaElem = isAlpha(elem);
                if ((isDigitElem && isAlphaElem) ||
                        (!isDigitElem && !isAlphaElem)) {
                    qDebug() << "Error: wrong data!" << elem;
                    return "";
                }
                tmpStr += elem;
                ++i;
                elem = *i;

            }
            std::reverse(tmpStr.begin(), tmpStr.end());
            stack.push(Data(tmpStr, optype::null));
            qDebug() << "В стек помещен элемент:" << tmpStr.c_str();
        }
        else if (isOperator(elem)) {
            Data firstArg;
            Data secondArg;
            qDebug() << "Знак оперции:" << elem;
            if (!stack.isEmpty()) {
                secondArg = stack.pop();
            }
            else {
                qDebug() << "Error: stack is empty";
                return "";
            }
            if (!stack.isEmpty()) {
                firstArg = stack.pop();
            }
            else {
                qDebug() << "Error: stack is empty!";
                return "";
            }
            qDebug() << "Выражения в стеке: " << firstArg.first.c_str() <<
                        "и" << secondArg.first.c_str();
            optype tmpOptype = optype::null;
            if (elem == '+') {
                tmpOptype = optype::plus;
            } else if (elem == '-') {
                tmpOptype = optype::minus;
            } else if (elem == '*') {
                tmpOptype = optype::multiply;
            } else if (elem == '^') {
                tmpOptype = optype::power;

            }

            if (secondArg.second != optype::null && secondArg.second < tmpOptype) {
                tmpStr += '(';
                tmpStr += secondArg.first;
                tmpStr += ')';
            } else {
                tmpStr += secondArg.first;
            }

            tmpStr += elem;

            if (firstArg.second != optype::null && firstArg.second < tmpOptype) {
                tmpStr += '(';
                tmpStr += firstArg.first;
                tmpStr += ')';
            } else {
                tmpStr += firstArg.first;
            }

            qDebug() << "Итоговое выражение помещается в стек:" << tmpStr.c_str();
            stack.push(Data(tmpStr, tmpOptype));
        }
        else {
            qDebug() << "Некорректный символ в строке!";
            return "";
        }
        tmpStr = "";
    }

    if (stack.size() == 1) {
        tmpStr = stack.pop().first;
        return tmpStr;
    }
    else {
        qDebug() << "Error: string is incorrect!" << stack.size() ;
        return "";
    }
}
