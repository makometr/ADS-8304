#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    dir = new QDir;
    in = new QTextStream;
    file = new QFile;

    ui->numberOfCity_spinBox->setRange(0, 1000);
    ui->startCity_spinBox->setRange(0, 1000);
    ui->endCity_spinBox->setRange(0, 1000);
    ui->readFromWindow_radioButton->setChecked(true);
}


MainWindow::~MainWindow()
{
    delete ui;
    delete file;
    delete dir;
    delete in;
}


void MainWindow::on_chek_pushButton_clicked()
{
    qDebug() << "Start PavingTheRoute";

    QStringList arrayStr;
    QString text;

    size_t startCity = 0;
    size_t endCity= 0;

    size_t numberOfCityes = 0;

    std::vector<std::vector <size_t>> roads;
    std::vector<bool> visited;

    size_t whereFrom = 0;
    size_t whereTo = 0;

    if (ui->readFromWindow_radioButton->isChecked()) {
        numberOfCityes = static_cast <size_t> (ui->numberOfCity_spinBox->value());

        if (numberOfCityes == 0) {
            qDebug() <<"Error, incorrect data";
            QMessageBox::critical(this, "Error", "Incorrect data!");
            return;
        } else {
            qDebug() <<"The number of cities:" << numberOfCityes;
        }

        roads.resize(numberOfCityes);
        visited.resize(numberOfCityes, false);

        startCity = static_cast <size_t> (ui->startCity_spinBox->value());
        endCity = static_cast <size_t> (ui->endCity_spinBox->value());

        text = ui->textEdit->toPlainText();
    }
    else if (ui->readFromFile_radioButton->isChecked()) {
        QString tmpStr = "";
        tmpStr = in->readLine();

        QStringList tmpList = tmpStr.split(" ");

        bool ok_0 = true;
        bool ok_1 = true;
        bool ok_2 = true;
        numberOfCityes = tmpList[0].toULongLong(&ok_2);
        startCity = tmpList[1].toULongLong(&ok_0);
        endCity = tmpList[2].toULongLong(&ok_1);

        if (ok_0 == false || ok_1 == false || ok_2 == false || numberOfCityes == 0
                || startCity >= numberOfCityes || endCity >= numberOfCityes ) {
            qDebug() <<"Error, incorrect data";
            QMessageBox::critical(this, "Error", "Incorrect data!");
            return;
        }

        if (numberOfCityes == 0) {
            qDebug() <<"Error, incorrect data";
            QMessageBox::critical(this, "Error", "Incorrect data!");
            return;
        } else {
            qDebug() <<"The number of cities:" << numberOfCityes;
        }

        roads.resize(numberOfCityes);
        visited.resize(numberOfCityes, false);

        text = in->readAll();
    }

    qDebug() << "List of existing roads:";

    arrayStr = text.split('\n');
    for (auto elem : arrayStr) {
        QStringList twoTown = elem.split(" ");

        if (twoTown.size() != 2) {
            qDebug() <<"Error, incorrect data";
            QMessageBox::critical(this, "Error", "Incorrect data!");
            return;
        }

        bool ok_0 = true;
        bool ok_1 = true;
        whereFrom = twoTown[0].toULongLong(&ok_0);
        whereTo = twoTown[1].toULongLong(&ok_1);

        if (ok_0 == false || ok_1 == false || whereFrom >= numberOfCityes || whereTo >= numberOfCityes) {
            qDebug() <<"Error, incorrect data";
            QMessageBox::critical(this, "Error", "Incorrect data!");
            return;
        } else {
            qDebug() << " Road from" << whereFrom << "to" << whereTo;
        }

        roads[whereFrom].push_back(whereTo);
        roads[whereTo].push_back(whereFrom);
    }

    if (startCity >= numberOfCityes || endCity >= numberOfCityes){
        qDebug() <<"Error, incorrect data";
        QMessageBox::critical(this, "Error", "Incorrect data!");
        return;
    }

    qDebug() << "Paving the route from" << startCity << "to" << endCity;
    PavingTheRoute(startCity, roads, visited);

    if (visited[endCity]) {
        qDebug() << "Success";
        QMessageBox::information(this, "Result", "Succes!");
    }
    else {
        qDebug() << "Sorry impossible to get directions";
        QMessageBox::warning(this, "Result", "No way");
    }

    qDebug() << "End PavingTheRoute";

    ui->readFromWindow_radioButton->setChecked(true);
    emit on_readFromWindow_radioButton_clicked();
}


void MainWindow::PavingTheRoute(size_t i, std::vector<std::vector<size_t>>& roads, std::vector<bool>& visited, size_t depth)
{
    visited[i] = true;

    std::string dbgStr = "";
    for (size_t i = 0; i < depth; ++i){
        dbgStr += "  ";
    }

    qDebug() << dbgStr.c_str() << "We are currently in the city " << i;

    for (size_t j = 0; j < roads[i].size(); ++j){
        if (visited[roads[i][j]] == false)
            PavingTheRoute(roads[i][j], roads, visited, depth + 1);
    }

    qDebug() << dbgStr.c_str() << "End of recursion";
}


void MainWindow::on_readFromFile_radioButton_clicked()
{
    file->close();

    ui->textLabel_0->setEnabled(false);
    ui->textLabel_1->setEnabled(false);
    ui->textLabel_2->setEnabled(false);
    ui->textLabel_3->setEnabled(false);
    ui->textEdit->setEnabled(false);
    ui->endCity_spinBox->setEnabled(false);
    ui->startCity_spinBox->setEnabled(false);
    ui->numberOfCity_spinBox->setEnabled(false);

    QString fileName = QFileDialog::getOpenFileName(this, "Open file", "", "*.txt");
    file->setFileName(fileName);
    file->open(QFile::ReadOnly | QFile::Text);
    in->setDevice(file);

    ui->openFile_textLabel->setText(fileName);
}


void MainWindow::on_readFromWindow_radioButton_clicked()
{
    file->close();

    ui->textLabel_0->setEnabled(true);
    ui->textLabel_1->setEnabled(true);
    ui->textLabel_2->setEnabled(true);
    ui->textLabel_3->setEnabled(true);
    ui->textEdit->setEnabled(true);
    ui->endCity_spinBox->setEnabled(true);
    ui->startCity_spinBox->setEnabled(true);
    ui->numberOfCity_spinBox->setEnabled(true);

    ui->openFile_textLabel->setText("none");
}

void MainWindow::on_test_pushButton_clicked()
{
    /*
     * Функция тестирования. Тестовые данные считываются из папки Tests
    */

    qDebug() << "Тестирование.";

    std::string expression = "";
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

        QStringList arrayStr;
        QString text;

        size_t startCity = 0;
        size_t endCity= 0;

        size_t numberOfCityes = 0;

        std::vector<std::vector <size_t>> roads;
        std::vector<bool> visited;

        size_t whereFrom = 0;
        size_t whereTo = 0;

        QString tmpStr = "";
        tmpStr = in->readLine();

        QStringList tmpList = tmpStr.split(" ");

        bool ok_0 = true;
        bool ok_1 = true;
        bool ok_2 = true;
        numberOfCityes = tmpList[0].toULongLong(&ok_2);
        startCity = tmpList[1].toULongLong(&ok_0);
        endCity = tmpList[2].toULongLong(&ok_1);

        if (ok_0 == false || ok_1 == false || ok_2 == false || numberOfCityes == 0
                || startCity >= numberOfCityes || endCity >= numberOfCityes ) {
            qDebug() <<"Error, incorrect data";
            QMessageBox::critical(this, "Error", "Incorrect data!");
            return;
        }

        if (numberOfCityes == 0) {
            qDebug() <<"Error, incorrect data";
            QMessageBox::critical(this, "Error", "Incorrect data!");
            return;
        } else {
            qDebug() <<"The number of cities:" << numberOfCityes;
        }

        roads.resize(numberOfCityes);
        visited.resize(numberOfCityes, false);

        text = in->readAll();

        qDebug() << "List of existing roads:";

        arrayStr = text.split('\n');
        for (auto elem : arrayStr) {
            QStringList twoTown = elem.split(" ");

            if (twoTown.size() != 2) {
                qDebug() <<"Error, incorrect data";
                QMessageBox::critical(this, "Error", "Incorrect data!");
                return;
            }

            bool ok_0 = true;
            bool ok_1 = true;
            whereFrom = twoTown[0].toULongLong(&ok_0);
            whereTo = twoTown[1].toULongLong(&ok_1);

            if (ok_0 == false || ok_1 == false || whereFrom >= numberOfCityes || whereTo >= numberOfCityes) {
                qDebug() <<"Error, incorrect data";
                QMessageBox::critical(this, "Error", "Incorrect data!");
                return;
            } else {
                qDebug() << " Road from" << whereFrom << "to" << whereTo;
            }

            roads[whereFrom].push_back(whereTo);
            roads[whereTo].push_back(whereFrom);
        }

        if (startCity >= numberOfCityes || endCity >= numberOfCityes){
            qDebug() <<"Error, incorrect data";
            QMessageBox::critical(this, "Error", "Incorrect data!");
            return;
        }

        qDebug() << "Paving the route from" << startCity << "to" << endCity;
        PavingTheRoute(startCity, roads, visited);

        if (visited[endCity]) {
            qDebug() << "Success";
            QMessageBox::information(this, "Result", "Succes!");
        }
        else {
            qDebug() << "Sorry impossible to get directions";
            QMessageBox::warning(this, "Result", "No way");
        }

        qDebug() << "End PavingTheRoute";
    }
}
