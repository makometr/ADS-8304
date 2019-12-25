#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QFileDialog>
#include <QGraphicsScene>
#include <QGraphicsTextItem>

#include <string>
#include <fstream>
#include <ctime>
#include <fstream>

#include "avl_tree.h"
#include "help.h"

using namespace std;

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private slots:

    void on_button_insert_clicked();

    void on_button_remove_clicked();

    void on_actionsave_triggered();

    void on_clear_clicked();

    void on_actionopen_triggered();

    void on_actioninfo_triggered();

    //void on_actionabout_triggered();

private:
    Ui::MainWindow *ui;
    //About *abt;
    QGraphicsScene* scene;

    void print_tree(node*, int, int);

    node* head = nullptr;
    QString qstr_tree = "";
    string str_tree = "(";
    time_t begin;
    time_t end;
    ofstream file;
};
#endif // MAINWINDOW_H
