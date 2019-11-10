#include <iostream>
#include <string>
#include <fstream>
#include <locale>
#include "binaryTree.h"


int main(int argc, char *argv[])
{
	std::cout << "\n\n=====Запуск программы=====\n";
    setlocale(LC_ALL, "RU");
    std::ifstream inputF;

	if (argc > 1)
        inputF.open(argv[1]);
    else
        inputF.open("input.txt");

    if (!inputF.is_open()) {
        std::cerr << "Невозможно открыть файл со входными данными";
        return 0;
    }


    std::ofstream outputF("output.txt");
    if (!outputF.is_open()) {
        std::cerr << "Невозможно открыть файл вывода";
        return 0;
    }

    BinaryTree<int> bt;
    bool readRes = bt.readTree(inputF);
	if (!readRes)
		return 0;

    std::cout << "Высота дерева: " << bt.calcHeight()<<"\n";
	std::cout << "Длина внутреннего пути: " <<bt.pathLength()<<"\n";
	std::cout << "Список листьев: ";
	outputF << "Список листьев: ";
	outputF << "\n";
	bt.printLeaves(outputF);
	std::cout << "\n";
    std::cout << "Узлов на уровне 3: " << bt.countNodesOnLevel(3) << "\n";


	outputF << "Высота дерева: " << bt.calcHeight()<<"\n";
	outputF << "Длина внутреннего пути: " <<bt.pathLength()<<"\n";
    outputF << "\nУзлов на уровне 3: " << bt.countNodesOnLevel(3) << "\n";
	
	std::cout << "\n\n=====Завершение программы=====\n\n";

    inputF.close();
    outputF.close();

    return 0;
}
