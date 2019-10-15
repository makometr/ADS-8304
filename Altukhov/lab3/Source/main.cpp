

#include <iostream>
#include <string>
#include <map>
#include <fstream>
#include <locale>

#include "queue.h"

typedef std::map<std::string, std::map<std::string, bool>> ChildrenArr; //ассоциативный двумерный массив arr[string][string] = bool

void readData(Queue* queue, ChildrenArr& children, std::ifstream& inputF);
void findDescendants(Queue* queue, ChildrenArr& children, std::ofstream& outputF);

int main(int argc, char* argv[]) {

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

	Queue* queue = new Queue;
	ChildrenArr children;
	readData(queue, children, inputF);
	findDescendants(queue, children, outputF);

	delete queue;
	inputF.close();
	outputF.close();

	return 0;
}

void readData(Queue* queue, ChildrenArr& children, std::ifstream& inputF) {
	std::string nextLine;
	std::cout << "\n=======Начало ввода=======\n\n";
	while ((std::getline(inputF, nextLine))) {
		int separator = nextLine.find(" ");
		if (separator > -1) {
			std::string parent = nextLine.substr(0, separator);
			std::string child = nextLine.substr(separator + 1);
			if ((parent.size() > 1) && (child.size() > 1)) {
				children[parent][child] = true;
				std::cout << parent << " " << child << "\n";
			}
		}
		else { //знак окончания ввода данных — одиночное имя
			std::cout << "Поиск потомков " << nextLine << "\n";
			queue->push(nextLine);
			std::cout << "\n=======Конец ввода========\n\n";
			return;
		}

	}
	std::cout << "Не указан предок, потомков которого надо найти.\n";
	std::cout << "\n=======Конец ввода========\n\n";
}

void findDescendants(Queue* queue, ChildrenArr& children, std::ofstream& outputF) {
	
	std::string names;
	bool childIsFound = false;
	while (!queue->isEmpty()) {
		std::string ancestor = queue->pop();
		std::map<std::string, bool> ::iterator it = children[ancestor].begin();
		for (int i = 0; it != children[ancestor].end(); it++, i++) { 
			if (it->second) {
				childIsFound = true;
				names += it->first + "; ";
				std::cout << i << ") Потомок " << it->first << " от " << ancestor << "\n";
				queue->push(it->first);
			}
		}
	}
	if (!childIsFound){
		std::cout << "Потомков не найдено.\n";
		outputF << "Потомков не найдено.\n";
	}
	else{
		outputF << names;
		std::cout << names << "\n";
	}
}
