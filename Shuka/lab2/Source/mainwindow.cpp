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
}


MainWindow::~MainWindow()
{
    delete ui;
    delete in;
    delete file;
    delete dir;
}


void MainWindow::on_readFile_checkBox_clicked()
{
    //выбор считывания из файла или из окна
    if (ui->readFile_checkBox->isChecked()) {
        file->close();

        ui->textLabel_0->setEnabled(false);
        ui->inputFirstList_lineEdit->setEnabled(false);
        ui->textLabel_1->setEnabled(false);
        ui->inputSecondList_lineEdit->setEnabled(false);

        QString fileName = QFileDialog::getOpenFileName(this,
                                                        "Open file");
        file->close();
        file->setFileName(fileName);
        file->open(QFile::ReadOnly | QFile::Text);
        in->setDevice(file);

        ui->openFile_textLabel->setText(fileName);
    }
    else {
        file->close();

        ui->textLabel_0->setEnabled(true);
        ui->inputFirstList_lineEdit->setEnabled(true);
        ui->textLabel_1->setEnabled(true);
        ui->inputSecondList_lineEdit->setEnabled(true);
        ui->openFile_textLabel->setText("none");
    }
}


void MainWindow::on_compare_pushButton_clicked()
{
    qDebug();
    qDebug() << "Сравнение списков:";

    std::string firstStr = "";
    std::string secondStr = "";

    //считывание строк из файла или из окна
    if (ui->readFile_checkBox->isChecked()) {
        firstStr = in->readLine().toStdString();
        secondStr = in->readLine().toStdString();
    }
    else {
        firstStr = ui->inputFirstList_lineEdit->text().toStdString();
        secondStr = ui->inputSecondList_lineEdit->text().toStdString();
    }

    //создание списков, проверка на корректность
    MyList::MyListP firstList(new MyList);
    MyList::MyListP secondList(new MyList);

    if (MyList::buildList(firstList, firstStr) &&
            MyList::buildList(secondList, secondStr)) {
        qDebug() << "Строки корректны, списки созданы";
    }
    else {
        qDebug() << "Строки некорректны!";
        QMessageBox::critical(this, "Result", "Входные данные неккоректны.");
        return;
    }

    qDebug() << "__Считанные списки__:";
    qDebug() << "Первый список:" << firstList;
    qDebug() << "Второй список:" << secondList;

    //сравнение списков
    if (MyList::compareList(firstList, secondList)) {
        qDebug() << "Списки структурно идентичны.";
        QMessageBox::information(this, "Result", "Списки структурно идентичны.");
    }
    else {
        qDebug() << "Списки НЕ структурно идентичны.";
        QMessageBox::warning(this, "Result", "Списки НЕ структурно идентичны.");
    }

    ui->readFile_checkBox->setChecked(false);
    ui->textLabel_0->setEnabled(true);
    ui->textLabel_1->setEnabled(true);
    ui->inputFirstList_lineEdit->setEnabled(true);
    ui->inputSecondList_lineEdit->setEnabled(true);
    ui->openFile_textLabel->setText("none");
}


void MainWindow::on_test_pushButton_clicked()
{
    /*
     * Функция тестирования. Тестовые данные считываются из папки Tests
    */

    qDebug() << "Тестирование.";

    std::string firstStr = "";
    std::string secondStr = "";
    dir->cd(QApplication::applicationDirPath() + "/Tests");
    QStringList listFiles = dir->entryList(QStringList("*.txt"), QDir::Files);

    for (auto fileName : listFiles) {
        if (fileName == "." || fileName == "..")
            continue;

        qDebug();
        qDebug() << "Тестовые данные из файла:" << fileName;

        file->close();
        file->setFileName(dir->path() + "/" + fileName);
        file->open(QFile::ReadOnly | QFile::Text);
        in->setDevice(file);

        while (!in->atEnd()) {
            firstStr = in->readLine().toStdString();
            secondStr = in->readLine().toStdString();

            MyList::MyListP firstList(new MyList);
            MyList::MyListP secondList(new MyList);

            if (MyList::buildList(firstList, firstStr) &&
                MyList::buildList(secondList, secondStr)) {
                qDebug() << "Строки корректны, списки созданы";
            }
            else {
                qDebug() << "Строки некорректны!";
                continue;
            }

            qDebug() << "__Считанные списки__:";
            qDebug() << "Первый список:" << firstList;
            qDebug() << "Второй список:" << secondList;

            //сравнение списков
            if (MyList::compareList(firstList, secondList)) {
                qDebug() << "_Списки структурно идентичны._";
            }
            else {
                qDebug() << "_Списки НЕ структурно идентичны._";
            }
            qDebug();
        }
    }
}
