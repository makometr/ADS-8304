#ifndef QUEUE
#define QUEUE

#include <string>

struct Elem;

struct Elem {
	std::string value;
	Elem* next;

	Elem() : next(nullptr) {}
	~Elem();
	void print() const;
};

class Queue {

private:
	Elem* head;
	Elem* last;

public:
	Queue() : head(nullptr), last(nullptr) {}
	~Queue();
	bool isEmpty() const;
	void push(std::string value);
	std::string pop();
	std::string top() const;
	void print() const;
};

#endif