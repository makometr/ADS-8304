#include "../Headers/referencewindow.h"
#include "ui_referencewindow.h"


ReferenceWindow::ReferenceWindow (QDialog* parent) :
    QDialog (parent),
    ui (new Ui::ReferenceWindow)
{
    ui->setupUi (this);

    connect (this, &ReferenceWindow::change_textBrowser_signal,
             this, &ReferenceWindow::change_textBrowser);
}


ReferenceWindow::~ReferenceWindow()
{
    delete ui;
}


void ReferenceWindow::on_fanoShannon_pushButton_clicked()
{
    emit (change_textBrowser_signal (":/HTML/GUI/HTML/Fano-"
                                     "ShannonAlgorithm.html"));
}


void ReferenceWindow::on_huffman_pushButton_clicked()
{
    emit (change_textBrowser_signal (":/HTML/GUI/HTML/HuffmanAlgorithm.html"));
}


void ReferenceWindow::on_decode_pushButton_clicked()
{
    emit (change_textBrowser_signal (":/HTML/GUI/HTML/DecodeAlgorithm.html"));
}


void ReferenceWindow::on_aboutTheProgram_pushButton_clicked()
{
    emit (change_textBrowser_signal (":/HTML/GUI/HTML/AboutTheProgram.html"));
}


void ReferenceWindow::change_textBrowser(const QString& fileName)
{
    QFile file (fileName);
    file.open (QFile::Text | QFile::ReadOnly);

    QString text = file.readAll();
    ui->textBrowser->setHtml (text);

    file.close();
}
