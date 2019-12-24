#include "../Headers/mainwindow.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
{

    //QRect screenSize = QApplication::desktop()->screenGeometry();
    //this->setGeometry(screenSize);
    resize(800,600);
    setWindowTitle("Хэш-таблица");
   // show();

    hashTable = nullptr;
    hashTable = new HashTable<std::string>;

    scroll = new QScrollArea(this);
    setCentralWidget(scroll);
    centralWidget = new QWidget();//запихнем в скролл попозже
    mainLayout = new QGridLayout(centralWidget);

    QSpacerItem* space = new QSpacerItem(1,10);
    mainLayout->addItem(space,4, 0, 1, 4);

    mainText = new QLabel("Чтобы начать, откройте файл или введите строку для обработки в текстовое окно и нажмите Enter.", centralWidget);
    mainText->setStyleSheet("font-size: 16px");
    mainLayout->addWidget(mainText, 0, 0, 1, 4, Qt::AlignHCenter | Qt::AlignTop);
   // mainText->setAlignment(Qt::AlignHCenter | Qt::AlignTop);

    space = new QSpacerItem(1,10);
    mainLayout->addItem(space,1, 0, 1, 4);

    openFileButton = new QPushButton("Открыть файл", centralWidget);
    openFileButton->setStyleSheet("font-size: 20px; height:50px");
    mainLayout->addWidget(openFileButton, 2, 0, 1, 2, Qt::AlignHCenter | Qt::AlignTop);
    connect(openFileButton, SIGNAL(clicked()), this, SLOT(openFileButtonListener()));

    clearAllButton = new QPushButton("Начать заново", centralWidget);
    clearAllButton->setStyleSheet("font-size: 20px; height:50px");
    mainLayout->addWidget(clearAllButton, 2, 2, 1, 2, Qt::AlignHCenter | Qt::AlignTop);
    connect(clearAllButton, SIGNAL(clicked()), this, SLOT(clearAllButtonListener()));

    space = new QSpacerItem(1,10);
    mainLayout->addItem(space,3, 0, 1, 4);

    textBox = new QTextEdit(centralWidget);
    mainLayout->addWidget(textBox, 4, 0, 1, 4);
    connect(textBox, SIGNAL(textChanged()), this, SLOT(enterLastLine()));
    textBox->setStyleSheet("font-size: 18px;");

    space = new QSpacerItem(1,10);
    mainLayout->addItem(space, 5, 0, 1, 4);



    tableWidget = new QWidget(centralWidget);
    mainLayout->addWidget(tableWidget, 7, 0, 1, 4);
    mainLayout->setRowStretch(7, 1);

    scroll->setWidget(centralWidget);
    scroll->setWidgetResizable(true);
}

MainWindow::~MainWindow()
{
    //все остальное в этих виджетах само удалится
    delete tableWidget;
    delete centralWidget;
    delete scroll;
    if (hashTable){
        delete hashTable;
    }
}

void MainWindow::openFileButtonListener(){

    QString fileName = QFileDialog::getOpenFileName(centralWidget,
                            QString::fromUtf8("Открыть файл"),
                            QDir::currentPath(),
                            "TXT (*.txt);;All files (*.*)");
    if (!fileName.isNull()){
       hashTable->drawHashTable(tableWidget);
       readFile(fileName.toStdString());
       hashTable->drawHashTable(tableWidget);
    }
}

void MainWindow::clearAllButtonListener(){
    if (hashTable){
        hashTable->clearDrawnHashTable(tableWidget);
        delete hashTable;
        hashTable = nullptr;
    }
    textBox->clear();
}

void MainWindow::readFile(std::string fileName){

    if (!hashTable)
        hashTable = new HashTable<std::string>;
    hashTable->clearHighlights();
    std::ifstream inputF(fileName);
    if (!inputF.is_open()) {

        createErrorMessage("Невозможно открыть файл со входными данными");
    }

    std::string nextLine;

    while (std::getline(inputF, nextLine)) {
      //  std::cout << "Введена строка: " << nextLine << "\n";
        hashTable->insert(nextLine);
    }

    inputF.close();
}

void MainWindow::createErrorMessage(QString text){

    QMessageBox::information(centralWidget,
                QString::fromUtf8("Ошибка"),
                text);

}

void MainWindow::enterLastLine(){ //если последний символ текстбокса - перенос, то анализируем строку и выполняем над ней нужную операцию
    QString text = textBox->toPlainText();
    if ((!text.isEmpty()) && text[text.length()-1]=='\n'){

        std::reverse(text.begin(), text.end());
        int res = text.indexOf('\n', 1);
        std::reverse(text.begin(), text.end());

        QString line;
        if (res>-1){
            line = text.right(res).section('\n', 0, -2);
        }
        else{
            line = text.section('\n', 0, -2);
        }
        if (!hashTable)
            hashTable = new HashTable<std::string>;
        hashTable->drawHashTable(tableWidget);
        hashTable->clearHighlights();
        QString mode;
        mode = line.length()>7 ? line.left(7) : "nomode ";
        if (mode == "insert "){
            hashTable->insert(line.right(line.length()-7).toStdString());
            hashTable->drawHashTable(tableWidget, line.right(line.length()-7).toStdString());
        }
        else if (mode == "delete "){
            hashTable->remove(line.right(line.length()-7).toStdString());
            hashTable->drawHashTable(tableWidget, line.right(line.length()-7).toStdString());
        }
        else{
            hashTable->insert(line.toStdString());
            hashTable->drawHashTable(tableWidget, line.toStdString());
        }

    }
}
