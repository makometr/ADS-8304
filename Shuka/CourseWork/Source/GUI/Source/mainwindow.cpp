#include "../Headers/mainwindow.h"
#include "ui_mainwindow.h"


MainWindow::MainWindow (QWidget *parent)
    : QMainWindow (parent), ui (new Ui::MainWindow)
{
    ui->setupUi (this);

    referenceWindow = new ReferenceWindow;
    inputFile = new QFile;
    graphicWindow = new GraphicWindow;

    connect (graphicWindow, &GraphicWindow::myCloseEvent,
             this, &MainWindow::show);

    connect (this, &MainWindow::demonstrateDecode,
             graphicWindow, &GraphicWindow::decoding);

    connect (this, &MainWindow::demonstrateHuffmanEncode,
             graphicWindow, &GraphicWindow::huffmanEncoding);

    connect (this, &MainWindow::demonstrateFanoShannonEncode,
             graphicWindow, &GraphicWindow::fanoShannonEncoding);
}


MainWindow::~MainWindow()
{
    delete ui;
    delete referenceWindow;
    delete graphicWindow;
    delete inputFile;
}


QString MainWindow::readFromFile (const QString& fileName)
{
    QFile file (fileName);

    file.open (QFile::Text | QFile::ReadOnly);

    if (!file.isOpen()) {
        return "";
    }

    QString text = file.readAll();

    file.close();

    return text;
}


void MainWindow::on_actionAbout_program_triggered()
{
    referenceWindow->setModal (true);
    referenceWindow->show();
}


void MainWindow::on_actionAbout_author_triggered()
{
    QString text = readFromFile (":/HTML/GUI/HTML/AboutTheAuthor.html");

    QMessageBox::information (this, "About the author", text);
}


void MainWindow::on_fanoShannonEncode_pushButton_clicked()
{
    QString fileName = QFileDialog::getOpenFileName (this, "Open file");
    QString text = readFromFile (fileName);

    if (text == "") {
        QMessageBox::warning(this, "Error", "Empty data");
        return;
    }

    this->close();

    emit (demonstrateFanoShannonEncode (text));
}


void MainWindow::on_huffmanEncode_pushButton_clicked()
{
    QString fileName = QFileDialog::getOpenFileName (this, "Open file");
    QString text = readFromFile (fileName);

    if (text == "") {
        QMessageBox::warning(this, "Error", "Empty data");
        return;
    }

    this->close();

    emit (demonstrateHuffmanEncode (text));
}


void MainWindow::on_decode_pushButton_clicked()
{
    QString fileName = QFileDialog::getOpenFileName (this, "Open file");
    QString text = readFromFile (fileName);

    if (text == "") {
        QMessageBox::warning(this, "Error", "Empty data");
        return;
    }

    this->close();

    emit (demonstrateDecode (text));
}
