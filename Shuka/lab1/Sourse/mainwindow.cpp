#include "mainwindow.h"
#include "ui_mainwindow.h"


MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    in = new QTextStream;
    file = new QFile;
}


MainWindow::~MainWindow()
{
    delete ui;
    delete in;
    delete file;
}


void MainWindow::on_check_pushButton_clicked()
{
    /*
     * При нажатии на кнопку "Check expression" происходит проверка выражения
     * с помощью рекурсивного алгоритма, реализованного в классе
     * SyntaxAnalysis
    */

    qDebug() << "Анализатор выражения.";

    if (ui->checkBox->isChecked()) {
        result = in->readAll().toStdString();
    }
    else {
        result = ui->lineEdit->text().toStdString();
    }

    qDebug() << "Считанная строка: " << result.c_str();

    auto it_begin = result.begin();
    auto it_end = result.end();

    if (isExpression(it_begin) && ++it_begin == it_end) {
        qDebug() << "Строка является выражением.";
        QMessageBox::information(this, "Result", "Строка является выражением.");
    }
    else {
        qDebug() << "Строка НЕ является выражением.";
        QMessageBox::warning(this, "Result", "Строка НЕ является выражением.");
    }

    ui->checkBox->setChecked(false);
    ui->label->setEnabled(true);
    ui->lineEdit->setEnabled(true);
}


void MainWindow::on_checkBox_clicked()
{

    /*
     * Переключение между считыванием из строки и из файла
    */

    if (ui->checkBox->isChecked()) {
        ui->label->setEnabled(false);
        ui->lineEdit->setEnabled(false);
        file->setFileName(QFileDialog::getOpenFileName(this,
                                                "Open file"));
        file->open(QFile::ReadOnly | QFile::Text);
        in->setDevice(file);
    }
    else {
        ui->label->setEnabled(true);
        ui->lineEdit->setEnabled(true);
    }
}


bool MainWindow::isExpression(std::string::iterator& pos,
                                  size_t depth) const
{
    std::string debugString = "";
    for (size_t i = 0; i < depth; ++i)
        debugString += " ";
    qDebug() << debugString.c_str() << __func__ << "глубина рекурсии:" << depth;

    if (isLetter(*pos)) {
        qDebug() << debugString.c_str() << "Выражение корректно";
        return true;
    }

    if (*pos == '(') {
        ++pos;
    }
    else {
        qDebug() << debugString.c_str() << "отсутствует '(' или 'идентификатор'";
        return false;
    }

    if (isExpression(pos, depth+1)) {
        ++pos;
    }
    else {
        qDebug() << debugString.c_str() << "отсутвует 'выражение'";
        return false;
    }

    if (isSign(*pos)) {
        ++pos;
    }
    else {
        qDebug() << debugString.c_str() << "отсутствует 'знак'";
        return false;
    }

    if (isExpression(pos, depth+1)) {
        ++pos;
    }
    else {
        qDebug() << debugString.c_str() << "отсутствует 'выражение'";
        return false;
    }

    if (*pos != ')') {
        qDebug() << debugString.c_str() << "отсутствует ')'";
        return false;
    }

    qDebug() << debugString.c_str() << "Выражение корректно";
    return true;
}


bool MainWindow::isLetter(const char ch) const
{
    //проверка символа на соответствие букве
    return ((ch >= 'a' && ch <= 'z') || (ch >= 'A' && ch <= 'Z'));
}


bool MainWindow::isSign(const char ch) const
{
    //проверка символа на соответствие знаку
    return (ch == '*' || ch == '+' || ch == '-');
}


void MainWindow::test()
{
    file->setFileName(QDir::currentPath() + "/Tests/test.txt");
    file->open(QFile::ReadOnly | QFile::Text);
    in->setDevice(file);

    std::string result;
    while ((result = in->readLine().toStdString()) != "") {
        auto it_begin = result.begin();
        auto it_end = result.end();

        qDebug();
        qDebug() << "Считанная строка:" << result.c_str();
        if (isExpression(it_begin) && ++it_begin == it_end) {
            qDebug() << "Строка является выражением.";
        }
        else {
            qDebug() << "Строка НЕ является выражением.";
        }
        qDebug();
    }
}
