#include <iostream>
#include <string>
#include "list.h"

void IerList::readData( IerList*& listToMerge, std::string str, int& iter){

	//смотрит символ с индексом iter, запускает собирание атома если считано число
	//в противном случае чтение продолжается функцией readSequence

	int prev = 0;
	char lastSymbol = str[iter];

	std::size_t pos = 0;
	if ( lastSymbol == ')' ){
		std::cerr << " ! List.Error 1 " << "\n"; 
		exit(1); 
	} 
	else if ( lastSymbol != '(' ) {
		
		if (isdigit(lastSymbol)){

			int tempIter = iter+1;
			int i = 0;
			
			while (isdigit(str[tempIter+i]))
				++i;
			
			prev = std::stoi(str.substr(iter, i+1), &pos, 10);
			iter += i;
			this->makeAtom(prev);
		}
	}
	else this->readSequence(listToMerge, str, iter);
} 

void IerList::readSequence(IerList*& listToMerge, std::string str, int& iter){//чтение, установление связей между частями списка

	IerList* list1;
	IerList* list2;

	if (!(str[++iter])) {
		std::cerr << " ! List.Error 2 " << "\n"; 
		exit(1);
	}
	else {

		while  ( str[iter]==' ' ) 
			++iter;
		if ( str[iter] == ')' ) {}//nothing 
		else {
			list1 = new IerList;
			list2 = new IerList;
			list1->readData(list1, str, iter);
			list2->readSequence(list2, str, iter);
			listToMerge->merge(list1, list2);
		} 
	}
}

void IerList::printSymbol() const {//печать отдельных атомов

	if ((this->isNull())) {
		std::cout << " () ";
		std::cout << "empty\n";
	}
	else if (this->isAtom()) 
		std::cout << ' ' << this->atom;
	else  { 
		std::cout << " (" ;
		this->writeSequence();
		std::cout << " )";
	}
}

void IerList::writeSequence() const { //рекурсивная печать списка

	if (!(this->isNull())) {
		this->getHead()->printSymbol(); 
		this->getTail()->writeSequence();
	}
}


IerList::~IerList(){
	if (!(this->isNull()) && !(this->isAtom()) ){
		delete this->getHead();
		delete this->getTail();
	}	
}


bool IerList::isNull() const { 

	if (!(this->tag) && (this->head == nullptr) && (this->tail == nullptr))
		return true;
	return false;
}


IerList* IerList::getHead() const {
	
	if (!this->isNull()) 
		if (!this->isAtom())	
			return this->head;
		else { 
			std::cerr << "Error: Head(atom) \n"; 				
			exit(1); 
		}
	else { 
		return nullptr;
	}
}

IerList* IerList::getTail() const {
	
	if (!this->isNull())
		if (!this->isAtom())	
			return this->tail;
		else { 
			std::cerr << "Error: Tail(atom) \n"; 
			exit(1); 
		}
	else { 
		return nullptr;
	}
}

IerList* IerList::getTrueTail() const { //обычный tail всегда является списком, а эта функция достает его первый элемент
	
	if (!this->isNull())
		if (!this->isAtom())
			if (!this->getTail()->isNull())
				return this->getTail()->getHead();
			else return nullptr;
		else { 
			std::cerr << "Error: True Tail(atom) \n"; 
			exit(1); 
		}
	else { 
		return nullptr;
	}
}

int IerList::getAtom() const {
	if (this->isNull() || !(this->isAtom())) {
		std::cout << "Нет атома!\n";
		return 0;
	}
	else
		return this->atom;
}

bool IerList::isAtom() const {	

	if (this->isNull()) 
		return false;
	else 
		return (this->tag);
}



void IerList::merge(IerList* head, IerList* tail){ 
	
	if (tail->isAtom()) { 
		std::cerr << "Error: cons(*, atom) \n"; 
		exit(1);
	}
	else { 
		this->tag = false;
		this->head = head;
		this->tail = tail;
	}
}

void IerList::makeAtom(const int x){ 

	this->tag = true;
	this->atom = x;

}	

void IerList::readList(IerList*& listToMerge, std::string str) { //функция-запускатор чтения списка
	char x = '\0';
	int iter = 0;
	do{ 
		if (x!='\0')
			++iter;
		x = str[iter];
		
	}
	while (x==' ');
	this->readData(listToMerge, str, iter);
}

void IerList::print() const {//функция-запускатор печатания списка
	this->printSymbol();
	std::cout<<"\n";
}	

bool IerList::isBalanceBeam() const {
	balanceBeamStatuses res = this->isNull() ? balanceBeamStatuses::noShoulder : this->goRoundBalanceBeam(false);
	std::string status;
	switch (static_cast<int>(res)){
		case 0:
			status = "Все хорошо";
			break;
		case 1:
			status = "Нет плеча";
			break;
		case 2:
			status = "Не указана длина";
			break;
		case 3:
			status = "Лишние значения";
			break;
		case 4:
			status = "Не указана масса";
			break;
	}
	std::cout << "Статус коромысла: " << status << "\n";
	return static_cast<int>(res)>0? false : true;
}	

balanceBeamStatuses IerList::goRoundBalanceBeam(bool isInShoulder) const {

	if (!(this->isNull()) ){
		
		if (!(isInShoulder)){ //если не в плече, то смотрим, есть ли два вложенных списка
			
			if ((this->getHead() != nullptr) && !(this->getHead()->isNull()) && !(this->getHead()->isAtom())) {}//okey	
			else return balanceBeamStatuses::noShoulder;
			
			if ((this->getTail() != nullptr) && !(this->getTail()->isNull()) && !(this->getTail()->isAtom())) {}//okey
			else return balanceBeamStatuses::noShoulder;
			
			balanceBeamStatuses res = this->getHead()->goRoundBalanceBeam(true); //запуск анализа левого плеча
			if (res == balanceBeamStatuses::noErrors)
				return this->getTrueTail()->goRoundBalanceBeam(true); //запуск анализа правого плеча
			else return res;
		}
		else { //если внутри плеча то проверка наличия длины и массы/коромысла
			
			if ((this->getHead() != nullptr) && !(this->getHead()->isNull()) &&(this->getHead()->isAtom()) ) {}//okey
			else return balanceBeamStatuses::noLength;
			
			if ((this->getTail() != nullptr) && !(this->getTail()->isNull()) && (this->getTail() != nullptr)){
				IerList* nextList = this->getTail();
				IerList* nextHead = this->getTrueTail();
				bool timeToRet = false;
				if (nextHead->isAtom() && (nextList->getTail() == nullptr || nextList->getTail()->isNull())){//length and mass
					timeToRet = true;
				}
				if (!(nextHead->isAtom()) && (nextList->getTail() == nullptr || nextList->getTail()->isNull())){//length and balance beam
					return nextHead->goRoundBalanceBeam(false); //запуск анализа наличия плечей вложенного коромысла
				}
				else if (!timeToRet){ 
					return balanceBeamStatuses::excessValues;
				}
				if (timeToRet)
					return balanceBeamStatuses::noErrors;
			}
			else
				return balanceBeamStatuses::noMass;
		}
	}
	return balanceBeamStatuses::noShoulder;
}	


