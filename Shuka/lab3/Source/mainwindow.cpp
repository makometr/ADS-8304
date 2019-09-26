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
    std::string result = MyStack::toInfix(tmpStr);
    if (result != "") {
        qDebug() << "Выражение в инфиксной форме: " << result.c_str();
        QMessageBox::information(this, "Result", result.c_str());
    }
    else {
        qDebug() << "Введенное выражение некорректно";
        QMessageBox::warning(this, "Result", "Введенное выражение некорректно");
    }

    ui->input_lineEdit->clear();
    ui->readFile_radioButton->setChecked(false);
    ui->readLineEdit_radioButton->setChecked(false);
    ui->readPostfix_radioButton->setChecked(true);
    ui->textLabel_1->setEnabled(false);
    ui->input_lineEdit->setEnabled(false);
    emit on_readPostfix_radioButton_clicked();
}
