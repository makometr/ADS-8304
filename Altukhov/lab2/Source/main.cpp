#include <iostream>
#include <string>
#include "list.h"
#include <stack>

void findWeight(IerList* list, int& weight){
	
	std::cout << "Смотрю в список:";
	list->print();
	if ((!(list->isNull())) && (list->getTail()!=nullptr) && ((list->getTrueTail() == nullptr)) && list->getHead()->isAtom() ){
		weight += list->getHead()->getAtom();
		std::cout << "Текущий вес: " << weight << "\n";
	}
	if ( (list->getHead() != nullptr) && (!(list->getHead()->isAtom()))  ){
	    findWeight(list->getHead(), weight);
	}
	if ( (list->getTail() != nullptr) && (!(list->getTail()->isAtom())) ){
		findWeight(list->getTail(), weight);
	}
	
}	

bool isListInString(std::string str){
	
	std::stack <char> inputStack;
	
	for (unsigned int i=0; i<str.length(); i++){
		
		if (str[i] == '(') {
			inputStack.push(str[i]);
		}
		else if (str[i] == ')') {
			if (inputStack.empty()){
				std::cout << "Не хватает открывающей скобки\n";
				return false;
			}
			inputStack.pop();
		}
		else if (str[i] == ' ' || isdigit(str[i])) {}//skip
		
		else{
			std::cout << "Использование запрещенных символов\n";
			return false;
		}
	}
	if (inputStack.empty()){
		return true;
	}
	std::cout << "Не хватает закрывающей скобки\n";
	return false;
}

int main(){
    
	std::string input;
	std::getline(std::cin, input );
	std::cout << "\n\n----------Введенная строка: "<< input << "\n\n";
	bool check = isListInString(input);
	if (!check){
		std::cout << "Некорректный ввод\n";
		return 0;
	}
	
	
    IerList* list = new IerList;
    list->readList(list, input);

    check = list->isBalanceBeam();
	if (!check){
		delete list;
		return 0;
	}

	int weight = 0;
	findWeight(list, weight);
	std::cout << "Вес: " << weight <<"\n";

	delete list;
    return 0;
}
