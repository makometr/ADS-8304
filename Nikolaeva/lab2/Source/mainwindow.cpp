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


void MainWindow::on_reverse_pushButton_clicked()
{
    qDebug() << "Start reverseList";

    HierarchicalList::ListPointer list(new HierarchicalList);
    std::string listStr;

    if (ui->readFromWindow_radioButton->isChecked()) {
        listStr = ui->input_lineEdit->text().toStdString();
    }
    else {
        listStr = in->readLine().toStdString();
    }

    if (HierarchicalList::buildList(list, listStr)) {
        qDebug() << "list is: " << list;
        HierarchicalList::reverseList(list);
        qDebug() << "list after reverse: " << list;
        QMessageBox::information(this, "Result", ("list after reverese:" + list->toStdString()).c_str());
    }
    else {
        QMessageBox::critical(this, "Result", "Wrong input data!");
        qDebug() << "input data is incorrect!";
    }

    ui->input_lineEdit->clear();
    qDebug() << "End reverseList";
}


void MainWindow::on_readFromFile_radioButton_clicked()
{
    file->close();
    ui->textLabel_0->setEnabled(true);
    ui->openFile_textLabel->setEnabled(true);
    ui->textLabel_1->setEnabled(false);
    ui->input_lineEdit->setEnabled(false);
    ui->input_lineEdit->clear();

    QString fileName = QFileDialog::getOpenFileName(this, "Open file", "", "*.txt");
    file->setFileName(fileName);
    file->open(QFile::ReadOnly | QFile::Text);
    in->setDevice(file);

    if (fileName != "")
        ui->openFile_textLabel->setText(fileName);
    else
        ui->openFile_textLabel->setText("none");
}


void MainWindow::on_readFromWindow_radioButton_clicked()
{
    file->close();

    ui->textLabel_0->setEnabled(false);
    ui->openFile_textLabel->setEnabled(false);
    ui->textLabel_1->setEnabled(true);
    ui->input_lineEdit->setEnabled(true);
    ui->input_lineEdit->clear();
    ui->openFile_textLabel->setText("none");
}
