#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    file = new QFile;
    in = new QTextStream;
    charTree = new MyBinaryTree<char>;
    dir = new QDir;
    ui->readFromWindow_radioButton->setChecked(true);
    ui->isExist_radioButton->setChecked(true);
}


MainWindow::~MainWindow()
{
    delete ui;
    delete dir;
    delete file;
    delete in;
    delete charTree;
}


void MainWindow::on_test_pushButton_clicked()
{
    /*
     * Функция тестирования. Тестовые данные считываются из папки Tests
    */

    ui->readFromFile_radioButton->setChecked(true);
    qDebug() << "Тестирование.";

    std::string elemStr;
    std::string treeStr;
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
            elemStr = in->readLine().toStdString();

            bool isIsExist = false;
            bool isCountElem = false;
            bool isMinHeightToElem = false;

            if (ui->isExist_radioButton->isChecked())
                isIsExist = true;
            else if (ui->countElem_radioButton->isChecked())
                isCountElem = true;
            else
                isMinHeightToElem = true;

            if (isIsExist)
                qDebug() << "Проверка на существование элемента:";
            else if (isCountElem)
                qDebug() << "Подсчет количества вхождений элемента в дерево:";
            else
                qDebug() << "Подсчет минимального пути до элемента в дереве:";

            if (elemStr.size() != 1) {
                qDebug() << "Некорректный элемент!";
            }
            else {
                qDebug() << "Считанный элемент: " << elemStr[0];
                if (readCharTree(charTree)) {
                    qDebug() << "Считанное дерево:";
                    qDebug() << charTree->toAssignmentList().c_str();
                    if (isIsExist) {
                        if(charTree->isExistElem(elemStr[0])) {
                            qDebug() << "Элемент есть в дереве";
                        }
                        else {
                            qDebug() << "Элемента нет в дереве!";
                        }
                    }

                    if (isCountElem) {
                        size_t count = charTree->countElem(elemStr[0]);
                        std::string result = "Number of elements: ";
                        result += std::to_string(count);
                        qDebug() << "Количество элементов в дереве: " << count;
                    }

                    if (isMinHeightToElem) {
                        int minHeightToElem = charTree->minHeightToElem(elemStr[0]);
                        std::string result = "Min. height to element: ";
                        result += std::to_string(minHeightToElem);
                        qDebug() << "Минимальный путь до элемента: " << minHeightToElem;
                    }
                }
                else {
                    qDebug() << "Некорректное дерево!";
                }
            }
            charTree->clearTree();
            qDebug();
        }
    }
    ui->readFromWindow_radioButton->setChecked(true);
}


void MainWindow::on_readFromWindow_radioButton_clicked()
{
    //выбор считывания из окна
    file->close();
    ui->tree_lineEdit->setEnabled(true);
    ui->textLabel_1->setEnabled(true);
    ui->elem_lineEdit->setEnabled(true);
    ui->textlabel_2->setEnabled(true);
    ui->openFile_textLabel->setText("none");
}


void MainWindow::on_readFromFile_radioButton_clicked()
{
    //выбор считывания из файла
    file->close();

    ui->textLabel_0->setEnabled(false);
    ui->tree_lineEdit->setEnabled(false);
    ui->elem_lineEdit->setEnabled(false);
    ui->textlabel_2->setEnabled(false);
    QString fileName = QFileDialog::getOpenFileName(this,
                                                    "Open file");
    file->setFileName(fileName);
    file->open(QFile::ReadOnly | QFile::Text);
    in->setDevice(file);

    ui->openFile_textLabel->setText(fileName);
}


bool MainWindow::readCharTree(MyBinaryTree<char> *charTree)
{
    /*
     * Функция считывания дерева
    */

    std::string tmpStr = "";

    //считывание строки из файла или из окна
    if (ui->readFromFile_radioButton->isChecked()) {
        tmpStr = in->readLine().toStdString();
    }
    else {
        tmpStr = ui->tree_lineEdit->text().toStdString();
    }

    //проверка строки на корректность и создание дерева
    qDebug() << "Считанная строка:" << tmpStr.c_str();
    if (isCorrectStr(tmpStr)) {
        charTree->createCharTree(tmpStr);
        return true;
    }
    else {
        return false;
    }
}


bool MainWindow::isCorrectStr(const std::string &str)
{
    /*
     * Проверка входной строки(дерева в упрощенной скобочной записи) на
     * корректность
    */

    bool isElem = false;
    bool flagIsCorrect = true;
    if (str[0] != '(') {
        qDebug() << "Скобочная запись бинарного дерева должна начинаться и заканчиваться скобками";
        return false;
    }
    if (str[str.length() - 1] != ')') {
        qDebug() << "Скобочная запись бинарного дерева должна начинаться и заканчиваться скобками";
        return false;
    }
    size_t indexStart;
    size_t numBrackets = 0;
    for (indexStart = 1; indexStart < str.length() - 1; indexStart++) {
        if (str[indexStart] != ' ' && str[indexStart] != '(' && str[indexStart] != ')') {
            if (!isElem) {
                isElem = true;
            }
            else {
                qDebug() << "Ошибка! Несколько элементов подряд без скобок";
                return false;
            }
        }
        if (str[indexStart] == '(') {
            if (!isElem) {
                qDebug() << "Не был добавлен эдемент в узел";
                return false;
            }
            numBrackets++;
            if (numBrackets > 2) {
                qDebug() << "Веток больше, чем 2";
                return false;
            }
            size_t indexEnd = indexStart;
            int openB = 1;
            int closeB = 0;
            while (openB > closeB) {
                indexEnd++;
                if (indexEnd >= str.length()) {
                    qDebug() << "Некорректный ввод строки";
                    return false;
                }
                if (str[indexEnd] == '(') {
                    openB++;
                }
                else if (str[indexEnd] == ')') {
                    closeB++;
                }
            }
            flagIsCorrect = flagIsCorrect && isCorrectStr(str.substr(indexStart, indexEnd - indexStart + 1));
            indexStart = indexEnd;
        }
    }
    if (str[indexStart] == ')') {
        if (!isElem) {
            qDebug() << "Не был добавлен элемент в узел";
            return false;
        }
        if (indexStart == str.length() - 1) {
            return flagIsCorrect;
        }
        else {
            qDebug() << "Некорректный ввод";
            return false;
        }
    }
    return false;
}


void MainWindow::on_do_pushButton_clicked()
{
    bool isIsExist = false;
    bool isCountElem = false;
    bool isMinHeightToElem = false;

    if (ui->isExist_radioButton->isChecked())
        isIsExist = true;
    else if (ui->countElem_radioButton->isChecked())
        isCountElem = true;
    else
        isMinHeightToElem = true;

    if (isIsExist)
        qDebug() << "Проверка на существование элемента:";
    else if (isCountElem)
        qDebug() << "Подсчет количества вхождений элемента в дерево:";
    else
        qDebug() << "Подсчет минимального пути до элемента в дереве:";


    std::string elem;
    if (ui->readFromWindow_radioButton->isChecked()) {
        elem = ui->elem_lineEdit->text().toStdString();
    }
    else {
        elem = in->readLine().toStdString();
    }

    if (elem.size() != 1) {
        qDebug() << "Некорректный элемент!";
        QMessageBox::critical(this, "Error", "Incorrect elem!");
    }
    else {
        qDebug() << "Считанный элемент: " << elem[0];
        if (readCharTree(charTree)) {
            qDebug() << "Дерево: ";
            qDebug() << charTree->toAssignmentList().c_str();
            if (isIsExist) {
                if(charTree->isExistElem(elem[0])) {
                    qDebug() << "Элемент есть в дереве";
                    QMessageBox::information(this, "Result", "Elem exist");
                }
                else {
                    qDebug() << "Элемента нет в дереве!";
                    QMessageBox::warning(this, "Result", "Elem doesn't exist");
                }
            }

            if (isCountElem) {
                size_t count = charTree->countElem(elem[0]);
                std::string result = "Number of elements: ";
                result += std::to_string(count);
                qDebug() << "Количество элементов в дереве: " << count;
                QMessageBox::information(this, "Result",  result.c_str());
            }

            if (isMinHeightToElem) {
                int minHeightToElem = charTree->minHeightToElem(elem[0]);
                std::string result = "Min. height to element: ";
                result += std::to_string(minHeightToElem);
                qDebug() << "Минимальный путь до элемента: " << minHeightToElem;
                QMessageBox::information(this, "Result",  result.c_str());
            }
        }
        else {
            qDebug() << "Некорректное дерево!";
            QMessageBox::critical(this, "Error", "Incorrect tree!");
        }
    }
    charTree->clearTree();
}
