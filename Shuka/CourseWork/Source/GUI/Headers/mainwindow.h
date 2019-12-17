#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QString>
#include <QMessageBox>
#include <QFile>
#include <QFileDialog>

#include "referencewindow.h"
#include "graphicwindow.h"


QT_BEGIN_NAMESPACE
namespace Ui
{
class MainWindow;
}
QT_END_NAMESPACE


class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow (QWidget* parent = nullptr);

    ~MainWindow();

signals:
    void demonstrateFanoShannonEncode (const QString& text);

    void demonstrateHuffmanEncode (const QString& text);

    void demonstrateDecode (const QString& text);

private slots:
    QString readFromFile (const QString& fileName);

    void on_actionAbout_program_triggered();

    void on_actionAbout_author_triggered();

    void on_fanoShannonEncode_pushButton_clicked();

    void on_huffmanEncode_pushButton_clicked();

    void on_decode_pushButton_clicked();

private:
    Ui::MainWindow* ui;
    ReferenceWindow* referenceWindow;
    GraphicWindow* graphicWindow;
    QFile* inputFile;
};

#endif // MAINWINDOW_H
