#include <iostream>
#include <fstream>
#include <string>

#include "RBST.h"

void readFromConsole(RandomBinarySearchTree<char> Tree)
{
    char choice,
         element;
    std::cout << "Редактирование Рандомизированного Бинарного Дерева Поиска\n"
                 "  1) Добавить элемент в РБДП\n"
                 "  2) Удалить элемент из РБДП\n"
                 "  3) Печать РБДП\n"
                 "  4) Выход из редактирования\n";
    std::cout << "Введите команду: ";
    std::cin >> choice;
    getchar();
    std::cout << std::endl;
    while(choice != '4')
    {
        switch(choice)
        {
            case '1':
                std::cout << "Введите элемент: ";
                std::cin >> element;
                getchar();
                Tree.searchAndInsertElement(element);
                std::cout << std::endl;
                break;
            case '2':
                std::cout << "Введите элемент: ";
                std::cin >> element;
                getchar();
                Tree.deleteElement(element);
                std::cout << std::endl;
                break;
            case '3':
                Tree.printTree(0);
                std::cout << std::endl;
                break;
            case '4':
                std::cout << "Выход";
                break;
            default:
                std::cout << "ОШИБКА: Неизвестная команда. Введите корректный номер команды." << std::endl;
                break;
        }
        if (choice != '4')
        {
            std::cout << "1 - Добавить, 2 - Удалить, 3 - Печать, 4 - Выход" << std::endl;
            std::cout << "Введите команду: ";
            std::cin >> choice;
            getchar();
            std::cout << std::endl;
        }
    }
    std::cout << "Конечное дерево:" << std::endl;
    Tree.printTree(0);
}

int readFromFile(const std::string& str, RandomBinarySearchTree<char> Tree)
{
    std::string str1;
    char element;
    std::cout << "Для файла: " << str << std::endl;
    std::ifstream inputFile(str);
    if (!inputFile.is_open())
    {
        std::cout << "ОШИБКА: Файл не открыт." << std::endl;
        return 0;
    }
    if (inputFile.eof())
    {
        std::cout << "ОШИБКА: Файл пуст." << std::endl;
        return 0;
    }
    while (inputFile >> element)
        Tree.searchAndInsertElement(element);
    Tree.printTree(0);
    readFromConsole(Tree);
    inputFile.close();
    return 0;
}

int main(int argc, char* argv[])
{
    setlocale(LC_ALL, "Russian");
    RandomBinarySearchTree<char> Tree;
    std::cout<< "_________________________________________\n"
                "         Курсовая работа на тему:\n"
                "            РАНДОМИЗИРОВАННОЕ\n"
                "                БИНАРНОЕ\n"
                "                 ДЕРЕВО\n"
                "                 ПОИСКА\n"
                "_________________________________________\n"
                "                     студент: Артем Бутко\n"
                "                      группа:        8304\n"
                "_________________________________________\n"<< std::endl;

    if (argc == 1)
    {
        char choice = 0;
        std::string str;
        std::cout << "Откуда Вы хотите считать бинарное дерево?" << std::endl;
        std::cout << "    1) Из файла.\n"
                     "    2) С консоли (пользовательский ввод).\n"
                     "    3) Выйти из программы.\n";
        std::cout << "Введите команду: ";
        std::cin >> choice;
        getchar();
        std::cout << std::endl;
        while (choice != '3')
        {
            switch (choice)
            {
                case '1':
                    std::cout << "____________Считывание из файла__________" << std::endl;
                    std::cout << "Введите путь до файла: ";
                    std::getline(std::cin, str);
                    readFromFile(str, Tree);
                    choice = '3';
                    break;
                case '2':
                    std::cout << "___________Считывание с консоли__________" << std::endl;
                    readFromConsole(Tree);
                    choice = '3';
                    break;
                case '3':
                    std::cout << "Выход из программы." << std::endl;
                    break;
                default:
                    std::cout << "ОШИБКА: ОШИБКА: Неизвестная команда. Введите корректный номер команды." << std::endl;
                    break;
            }
            if (choice != '3')
            {
                std::cout << "Введите команду: ";
                std::cin >> choice;
                getchar();
                std::cout << std::endl;
            }
        }

    }
    else readFromFile(argv[1], Tree);
    return 0;
}