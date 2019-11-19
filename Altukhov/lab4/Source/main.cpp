#include <iostream>
#include <string>
#include <fstream>
#include <locale>
#include <sstream>
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
		if (argc == 1)
			std::cerr << " input.txt";
		else
			std::cerr << " " << argv[1];
		std::cerr << "\n";
        return 0;
    }


    std::ofstream outputF("output.txt");
    if (!outputF.is_open()) {
        std::cerr << "Невозможно открыть файл вывода output.txt\n";
        return 0;
    }
	
    BinaryTree<int> bt;
	std::string binTreeString;
	std::getline(inputF, binTreeString);
	int level = 1;
	inputF >> level;
	std::istringstream inputString(binTreeString);//на всякий разделим на разные потоки
    bool readRes = bt.readTree(inputString);
	if (!readRes)
		return 0;

    std::cout << "Высота дерева: " << bt.calcHeight()<<"\n";
	std::cout << "Длина внутреннего пути: " <<bt.pathLength()<<"\n";
	std::cout << "Список листьев: ";
	outputF << "Список листьев: ";
	outputF << "\n";
	bt.printLeaves(outputF);
	std::cout << "\n";
	if (level>0)
		std::cout << "Узлов на уровне "<<level<<": " << bt.countNodesOnLevel(level) << "\n";
	else
		std::cout << "Не указан уровень для подсчета узлов\n";

	outputF << "Высота дерева: " << bt.calcHeight()<<"\n";
	outputF << "Длина внутреннего пути: " <<bt.pathLength()<<"\n";
	if (level>0)
		outputF << "\nУзлов на уровне "<<level<<": " << bt.countNodesOnLevel(level) << "\n";
	else
		outputF << "Не указан уровень для подсчета узлов\n";
	std::cout << "\n\n=====Завершение программы=====\n\n";

    inputF.close();
    outputF.close();

    return 0;
}
