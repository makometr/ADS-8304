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

void MainWindow::on_create_pushButton_clicked()
{
    qDebug();
    qDebug() << "Создание линейного списка:";

    std::string inpStr = "";
    inpStr = ui->lineEdit->text().toStdString();

        //создание списков, проверка на корректность
    MyList::MyListP List(new MyList);

    if (MyList::buildList(List, inpStr)) {
        qDebug() << "Строка корректна, иерархический список создан";
        }
    else {
            qDebug() << "Строка некорректна!";
            QMessageBox::critical(this, "Result", "Входные данные неккоректны.");
            return;
        }

        qDebug() << "__Считанный спискок__:";
        qDebug() << "Список:" << List;
        std::list<char> new_list;
        new_list = {};
        create_new_list(List, &new_list, 1);
        print_list(new_list);
}

void MainWindow::create_new_list(MyList::MyListP inp_list, std::list<char>* new_list, int depth){
    depth++;
    if(inp_list->isNull())
        return;
    while(!inp_list->isNull()){
        if(inp_list->getHead()->getIsAtom()){
            new_list->push_back(inp_list->getHead()->getAtom());
            inp_list = inp_list->getTail();
        }
        else {
            create_new_list(inp_list->getHead(), new_list, depth);
            inp_list = inp_list->getTail();
        }
    }
}

void MainWindow::print_list(std::list<char> list){
    auto begin = list.begin();
    auto end = list.end();
    std::cout<<"(";
    for(auto i = list.begin(); i != list.end(); i++){
       std::cout <<*i;
    }
    std::cout <<")"<<std::endl;
}


void MainWindow::on_test_pushButton_clicked(){
    /*
     * Функция тестирования. Тестовые данные считываются из папки Tests
    */

    qDebug() << "Тестирование.";
    std::string firstStr = "";
    QFile file(QApplication::applicationDirPath() + "/Tests/test_correct.txt");
    file.open(QIODevice::ReadOnly);


        qDebug();


        while (!file.atEnd()) {
            firstStr = file.readLine().toStdString();
            firstStr[firstStr.size() - 1] = '\0';
            MyList::MyListP firstList(new MyList);

            if (MyList::buildList(firstList, firstStr)) {
                qDebug() << "Строка корректна, список создан";
            }
            else {
                qDebug() << "Cписок создан";
                continue;
            }

            qDebug() << "Список:" << firstList;


            qDebug();
        }
        std::string secondStr = "";
        QFile file2(QApplication::applicationDirPath() + "/Tests/test_incorrect.txt");
        file2.open(QIODevice::ReadOnly);


            qDebug();


            while (!file2.atEnd()) {
                secondStr = file2.readLine().toStdString();
                secondStr[secondStr.size() - 1] = '\0';
                MyList::MyListP secondList(new MyList);

                if (MyList::buildList(secondList, secondStr)) {
                    qDebug() << "Строка корректна, список создан";
                }
                else {
                    qDebug() << "Cтрока некорректна!";
                    continue;
                }

                qDebug() << "Список:" << secondList;

                qDebug();
            }
}
