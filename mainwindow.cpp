#include "mainwindow.h"
#include "ui_mainwindow.h"



MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    ui->line_insert->clear();
    ui->line_remove->clear();

    abt = new About;
    scene = new QGraphicsScene(this);
    ui->visualiztion->setScene(scene);
}


MainWindow::~MainWindow()
{
    delete ui;
    delete scene;
    delete abt;
}


void MainWindow::on_button_insert_clicked()
{
    scene->clear();
    head = insert(head, int(stoi(ui->line_insert->text().toStdString())));

    print_tree(head, ui->visualiztion->geometry().x() / 2, 25);
    str_tree.clear();
    str_tree = "(";
    txt_tree(head, str_tree);

    ui->avl_tree->setText(QString::fromStdString(str_tree));
}


void MainWindow::on_button_remove_clicked()
{
    scene->clear();
    head = remove(head, int(stoi(ui->line_remove->text().toStdString())));
    print_tree(head, ui->visualiztion->geometry().x() / 2, 25);

    str_tree.clear();
    str_tree = "(";
    txt_tree(head, str_tree);

    ui->avl_tree->setText(QString::fromStdString(str_tree));
}


void MainWindow::on_clear_clicked()
{
    foreach (QGraphicsItem* item, scene->items()) {
          delete item;
    }


    head = delete_tree(head);
    str_tree.clear();
    str_tree = "(";


    ui->line_insert->clear();
    ui->line_remove->clear();
    ui->avl_tree->clear();

}


void MainWindow::on_actionsave_triggered()
{
    QString path = QFileDialog::getOpenFileName(this, tr("Open path to save"), "/home/egor/Desktop");

    if (path == nullptr) return;

    ofstream file(path.toStdString());

    file << (str_tree == "(" ? "( )" : str_tree);
}



void MainWindow::on_actionopen_triggered()
{
    QString path = QFileDialog::getOpenFileName(this, tr("Open path to download tree"), "/home/egor/Desktop");

    if (path == nullptr) return;

    ifstream oFile(path.toStdString());

    string str;
    oFile >> str;
    for (unsigned long i = 0; i < str.size(); i++)
    {
        if (str[i] == '(' or str[i] == ')' or str[i] == '#')
        {
            str[i] = ' ';
        }
    }
    stringstream sstream;
    int tmp;

    sstream << str;

    head = delete_tree(head);
    str_tree.clear();
    ui->avl_tree->clear();
    ui->line_insert->clear();
    ui->line_remove->clear();
    str_tree = "(";

    while(sstream >> tmp)
    {
        head = insert(head, tmp);
    }

    txt_tree(head, str_tree);
    ui->avl_tree->setText(QString::fromStdString(str_tree));

    print_tree(head, ui->visualiztion->geometry().x() / 2, 25);

}


void MainWindow::on_actioninfo_triggered()
{
    (new HelpBrowser (":/docs/doc", "index.htm"))->show();
}

void MainWindow::on_actionabout_triggered()
{
    abt->show();
}

void MainWindow::print_tree(node* tree, int x, int y)
{
    if (!tree) return;

    const int offset = 30;
    const int r = 25;

    if (tree->left)
    {
        QLine line(x + r, y + r, x - offset * tree->left->height * tree->left->height + 10, y + 90);
        scene->addLine(line, QPen(Qt::black));
    }

    if (tree->right)
    {
        QLine line(x + r, y + r, x + offset * tree->right->height * tree->right->height + 35, y + 90);
        scene->addLine(line, QPen(Qt::black));
    }


    scene->addEllipse(x, y, 2 * r, 2 * r , QPen(Qt::black), QBrush(Qt::white));

    int temp = tree->key;

    int count_zero = 1;
    while (temp /= 10)
        count_zero++;

    QString zeroes = (tree->key >= 0 ? "" : "-");
    for (int i = 0; i < 4 - count_zero; i++)
        zeroes += '0';

    QGraphicsTextItem* txtItem =
            new QGraphicsTextItem(zeroes + QString::number(abs(tree->key)));

    if (tree->key >= 0)
        txtItem->setPos(x + 7, y + 15);
    else
        txtItem->setPos(x + 4, y + 15);

    scene->addItem(txtItem);

    if (tree->left) {
        print_tree(tree->left, x - offset * tree->left->height * tree->left->height, y + 75);
   }

    if (tree->right) {
        print_tree(tree->right, x + offset * tree->right->height * tree->right->height, y + 75);
    }
}
