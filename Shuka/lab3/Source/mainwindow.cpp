#include "mainwindow.h"
#include "ui_mainwindow.h"


MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    file = new QFile;
    in = new QTextStream;
    dir = new QDir;

    ui->readPostfix_radioButton->setChecked(true);
    emit on_readPostfix_radioButton_clicked();
}


MainWindow::~MainWindow()
{
    delete ui;
    delete in;
    delete file;
    delete dir;
}


void MainWindow::on_readFile_radioButton_clicked()
{
    //выбор считывания из файла или из окна
    file->close();

    ui->textLabel_1->setEnabled(false);
    ui->input_lineEdit->setEnabled(false);
    QString fileName = QFileDialog::getOpenFileName(this,
                                                    "Open file");
    file->setFileName(fileName);
    file->open(QFile::ReadOnly | QFile::Text);
    in->setDevice(file);

    ui->openFile_textLabel->setText(fileName);
}


void MainWindow::on_readLineEdit_radioButton_clicked()
{
    file->close();

    ui->input_lineEdit->setEnabled(true);
    ui->textLabel_1->setEnabled(true);
    ui->openFile_textLabel->setText("none");
}


void MainWindow::on_readPostfix_radioButton_clicked()
{
    file->close();

    ui->input_lineEdit->clear();
    ui->input_lineEdit->setEnabled(false);
    ui->textLabel_1->setEnabled(false);

    QString fileName = QDir::currentPath() + "/Tests/postfix.txt";
    file->setFileName(fileName);
    file->open(QFile::ReadOnly | QFile::Text);
    in->setDevice(file);

    ui->openFile_textLabel->setText(fileName);
}


void MainWindow::on_toInfix_pushButton_clicked()
{
    qDebug();
    qDebug() << "Преобразование выражения из постфиксной в инфиксную форму:";

    //строка для считанного результата
    std::string tmpStr = "";

    //считывание строки из файла или из окна
    if (ui->readFile_radioButton->isChecked() ||
            ui->readPostfix_radioButton->isChecked()) {
        tmpStr = in->readLine().toStdString();
    }
    else {
        tmpStr = ui->input_lineEdit->text().toStdString();
    }

    qDebug() << "__Считанное выражение__:" << tmpStr.c_str();

    //Преобразование выражения в инфиксную форму
    MyStack *stack = new MyStack;
    std::string result = MainWindow::toInfix(stack, tmpStr);
    if (result != "") {
        qDebug() << "Выражение в инфиксной форме: " << result.c_str();
        QMessageBox::information(this, "Result", result.c_str());
    }
    else {
        qDebug() << "Введенное выражение некорректно";
        QMessageBox::warning(this, "Result", "Введенное выражение некорректно");
    }
    delete stack;

    ui->input_lineEdit->clear();
    ui->readFile_radioButton->setChecked(false);
    ui->readLineEdit_radioButton->setChecked(false);
    ui->readPostfix_radioButton->setChecked(true);
    ui->textLabel_1->setEnabled(false);
    ui->input_lineEdit->setEnabled(false);
    emit on_readPostfix_radioButton_clicked();
}

std::string MainWindow::toInfix(MyStack* stack, const std::string &expression)
{
    /*
     * Статический метод класса, для преобразования выражения,
     * заданного в постфиксной форме, в инфиксную.
     *
     * Принимает на вход константную ссылку на строку-выражение, возвращает
     * выражение в инфиксной форме, если исходное выражение корректно и пустую
     * строку в случае ошибки.
     *
     * Строка анализируется посимвольно. Если текущий символ "число или буква", тогда
     * элемент помещается в стек с приоритетом 0, если текущий символ "знак операции",
     * из стека достаются два элемента, записываются в временную строку с учетом приоритетов
     * операций и временная строка помещается в стек с приоритетом знака.
     *
     * В ходе преобразования, если стек пустой, выводится ошибка и возвращается пустая
     * строка. После преобразования в стеке должен находиться один элемент - инфиксное выражение.
    */

    std::string tmpStr = "";

    for (auto i = expression.cbegin(); i < expression.end(); ++i) {
        char elem = *i;
        if (elem == ' ') {
            continue;
        }
        else if (isDigit(elem) || isAlpha(elem)) {
            bool isDigitElem = isDigit(elem);
            while (elem != ' ' && i != expression.end()) {
                if ((isDigitElem && isAlpha(elem)) ||
                    (!isDigitElem && !isAlpha(elem))) {
                    qDebug() << "Error: wrong data!";
                    return "";
                }
                tmpStr += elem;
                ++i;
                elem = *i;
            }
            stack->push(Data(tmpStr, optype::null));

            qDebug() << "В стек помещается элемент:" << elem;
        }
        else if (isSign(elem)) {
            Data firstArg;
            Data secondArg;

            qDebug() << "Знак оперции:" << elem;

            if (!stack->isEmpty()) {
                secondArg = stack->top();
                stack->pop();
            }
            else {
                qDebug() << "Error: stack is empty!";
                return "";
            }

            if (!stack->isEmpty()) {
                firstArg = stack->top();
                stack->pop();
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

            if (firstArg.second != optype::null && firstArg.second < tmpOptype) {
                tmpStr += '(';
                tmpStr += firstArg.first;
                tmpStr += ')';
            } else {
                tmpStr += firstArg.first;
            }

            tmpStr += elem;

            if (secondArg.second != optype::null && secondArg.second < tmpOptype) {
                tmpStr += '(';
                tmpStr += secondArg.first;
                tmpStr += ')';
            } else {
                tmpStr += secondArg.first;
            }

            qDebug() << "Итоговое выражение помещается в стек:" << tmpStr.c_str();

            stack->push(Data(tmpStr, tmpOptype));
        }
        else {
            qDebug() << "Некорректный символ в строке!";
            return "";
        }
        tmpStr = "";
    }

    if (stack->size() == 1) {
        tmpStr = stack->top().first;
        stack->pop();
        return tmpStr;
    }
    else {
        qDebug() << "Error: string is incorrect!";
        return "";
    }
}


bool MainWindow::isDigit(const char ch)
{
    /*
     * Проверка на цифру
    */

    return (ch >= '0' && ch <= '9');
}


bool MainWindow::isAlpha(const char ch)
{
    /*
     * Проверка на букву
    */

    return ((ch >= 'a' && ch <= 'z') ||
            (ch >= 'A' && ch <= 'Z'));
}


bool MainWindow::isSign(const char ch)
{
    /*
     * Проверка на знак
    */

    return (ch == '+' || ch == '-' ||
            ch == '*' || ch == '^');
}
