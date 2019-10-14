#include "queue.h"

#include <iostream>

Elem::~Elem() {

	if (this->next)
		delete this->next;
}

void Elem::print() const {

	std::cout << this->value << "; ";
	if (this->next != nullptr)
		this->next->print();
}

Queue::~Queue() {

	if (!this->isEmpty())
		delete this->head;
}

bool Queue::isEmpty() const {
	if (this->head == nullptr)
		return true;
	return false;
}

void Queue::push(std::string value) {

	if (this->isEmpty()) {
		this->last = new Elem;
		this->last->value = value;
		this->head = this->last;
	}
	else {
		this->last->next = new Elem;
		this->last = this->last->next;
		this->last->value = value;
	}
}

std::string Queue::pop() {

	if (this->isEmpty()) {
		std::cerr << "Очередь пуста!\n";
		return "";
	}
	else {
		std::string returnVal = this->head->value;
		Elem* newHead = this->head->next;
		this->head->next = nullptr;
		delete this->head;

		this->head = newHead;
		if (this->head == nullptr) {
			this->last = nullptr;
		}
		return returnVal;
	}
}

std::string Queue::top() const {

	if (this->isEmpty()) {
		std::cerr << "Очередь пуста!\n";
		return "";
	}
	return this->head->value;
}

void Queue::print() const {

	if (this->isEmpty()) {
		std::cout << "()\n";
		return;
	}
	std::cout << "( ";
	this->head->print();
	std::cout << ")\n";
}