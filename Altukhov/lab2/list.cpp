#include <iostream>
#include <string>
#include "list.h"

void IerList::readData( IerList*& y, std::string str, int& iter){
	
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
	else this->readSequence(y, str, iter);
} 

void IerList::readSequence(IerList*& y, std::string str, int& iter){	

	IerList* list1,* list2;

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
			y->merge(list1, list2);
		} 
	}
}

void IerList::printSymbol(){

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

void IerList::writeSequence(){

	if (!(this->isNull())) {
		this->getHead()->printSymbol(); 
		this->getTail()->writeSequence();
	}
}

IerList::IerList():tag(false), head(nullptr), tail(nullptr) {}

IerList::~IerList(){
	if (!(this->isNull()) && !(this->isAtom()) ){
		delete this->getHead();
		delete this->getTail();
	}	
	delete this;
}


bool IerList::isNull(){ 

	if (!(this->tag) && (this->head == nullptr) && (this->tail == nullptr))
		return true;
	return false;
}


IerList::IerList* getHead(){
	
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

IerList* IerList::getTail(){
	
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

IerList* IerList::getTrueTail(){
	
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

int IerList::getAtom(){
	if (this->isNull() || !(this->isAtom())) {
		std::cout << "Нет атома!\n";
		return 0;
	}
	else
		return this->atom;
}

bool IerList::isAtom(){	

	if (this->isNull()) 
		return false;
	else 
		return (this->tag);
}



void IerList::merge(IerList* head, IerList* tail){ //costruct 1ist
	
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

void IerList::makeAtom(const int x){ //construct atom

	this->tag = true;
	this->atom = x;

}	

void IerList::readList(IerList*& y, std::string str){
	char x = '\0';
	int iter = 0;
	do{ 
		if (x!='\0')
			++iter;
		x = str[iter];
		
	}
	while (x==' ');
	this->readData(y, str, iter);
}

void IerList::print(){
	this->printSymbol();
	std::cout<<"\n";
}	

bool IerList::isBalanceBeam(){
	int res = this->goRoundBalanceBeam(false);
	std::string status = "";
	switch (res){
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
	std::cout << "Статус коромысла: " << string << "\n";
	return res>0? false : true;
}	

int IerList::goRoundBalanceBeam(bool isInShoulder){	

	if (!(this->isNull()) ){
		
		if (!(isInShoulder)){
			
			if ((this->getHead() != nullptr) && !(this->getHead()->isNull()) && !(this->getHead()->isAtom())) {}//okey	
			else return 1;//no shoulder
			
			if ((this->getTail() != nullptr) && !(this->getTail()->isNull()) && !(this->getTail()->isAtom())) {}//okey
			else return 1;//no shoulder
			
			int res = this->getHead()->goRoundBalanceBeam(true);
			if (!res)
				return this->getTrueTail()->goRoundBalanceBeam(true);
			else return res;
		}
		else {
			
			if ((this->getHead() != nullptr) && !(this->getHead()->isNull()) &&(this->getHead()->isAtom()) ) {}//okey
			else return 2;//no length
			
			if ((this->getTail() != nullptr) && !(this->getTail()->isNull()) && (this->getTail() != nullptr)){
				IerList* nextList = this->getTail();
				IerList* nextHead = this->getTrueTail();
				bool timeToRet = false;
				if (nextHead->isAtom() && (nextList->getTail() == nullptr || nextList->getTail()->isNull())){//length and mass
					timeToRet = true;
				}
				if (!(nextHead->isAtom()) && (nextList->getTail() == nullptr || nextList->getTail()->isNull())){//length and balance beam
					return nextHead->goRoundBalanceBeam(false);
				}
				else if (!timeToRet){ 
					return 3; //more then two values
				}
				if (timeToRet)
					return 0;
			}
			else
				return 4; //less then two values
		}
	}
}	


