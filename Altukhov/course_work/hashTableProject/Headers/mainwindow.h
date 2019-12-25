#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <iostream>
#include <fstream>
#include <string>
#include <algorithm>

#include "qtfiles.h"
#include "HashTable.h"
class MainWindow : public QMainWindow
{
    Q_OBJECT

private:
    QWidget* centralWidget; //почти центральный виджет
    QGridLayout* mainLayout;
    QWidget* tableWidget; //для хэштаблицы
    QLabel* mainText;
    QPushButton* openFileButton;
    QPushButton* clearAllButton;
    QTextEdit* textBox;
    QScrollArea* scroll; //скролл окна

    HashTable<std::string>* hashTable;
    void readFile(std::string fileName);
    void createErrorMessage(QString text);

private slots:
    void openFileButtonListener();
    void clearAllButtonListener();
    void enterLastLine();//ввод из текстбокса
public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();
};

#endif // MAINWINDOW_H
