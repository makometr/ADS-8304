

#include <iostream>
#include <locale>
#include <fstream>

#include "HashTable.h"

int main(int argc, char* argv[]) {
	setlocale(LC_ALL, "Russian");

	std::cout << "\n\n=====Запуск программы=====\n\n\n";

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


	HashTable hashTable;

	std::string nextLine;

	while (std::getline(inputF, nextLine) && (nextLine != "0")) { //0 - разделитель между стартовыми данными и данными, которые надо проверить
		hashTable.insert(nextLine);
	}

	hashTable.checkCollisions();
	std::cout << "\n\n";

	while (std::getline(inputF, nextLine)) {
		std::cout << "Введена строка " << nextLine << "\nПоиск в таблице...";
		outputF << "Введена строка " << nextLine << "\nПоиск в таблице...";
		if (hashTable.find(nextLine, hashTable.getLen())) {
			std::cout << " Найдено.\n";
			outputF << " Найдено.\n";
		}
		else {
			std::cout << " Не найдено. Элемент добавлен в таблицу.\n";
			outputF << " Не найдено. Элемент добавлен в таблицу.\n";
			hashTable.insert(nextLine);
		}
	}
	hashTable.checkCollisions();

	inputF.close();
	outputF.close();

	std::cout << "\n\n=====Завершение программы=====\n\n";

	return 0;
}

