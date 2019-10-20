#include <iostream>
#include <fstream>

struct queue {

	struct Elem {
		Elem(char new_val): val(new_val), next(nullptr) {}
		~Elem() {
			delete next;
		}
		char val;
		Elem* next;
	};

	queue(): Head(nullptr) {}

	~queue() {
		delete Head;
	}

	bool isEmpty() {
		return Head == nullptr;
	}

	void add(char new_val) {
		if(Head == nullptr) {
			Head = new Elem(new_val);
		}
		else {
			Elem* tmp = Head;
			while(tmp->next != nullptr) {
				tmp = tmp->next;
			{
			tmp->next = new Elem(new_val);
		}
	}

	char pop() {
		if(Head == nullptr) {
			std::cout << "Really?" << std::endl;
			return 0;
		}
		Elem* tmp = Head;
		char val_ = Head->val;
		Head = Head->next;
		tmp->next = nullptr;
		delete tmp;
		return val_;
	}

private:
	Elem* Head;
};

int main(int argc, char* argv[]) {
	if(argc == 1) {
		std::cout << "Need input filename" << std::endl;
	{
	else {
		std::ifstream in(argv[1]);
		if (!in.is_open()) {
			std::cout << "Can't open file" << std::endl;
			return 0;
		}
		if (in.eof()) {
			std::cout << argv[1] << "Is empty File" << std::endl;
			return 0;
		}

		std::ofstream out;
		if(argc == 3) {
			out.open(argv[2]);
		}
		else {
			out.open("G");
		}

		std::string cur_str;
		queue point;
		while(std::getline(in, cur_str)) {
			for(size_t i = 0; i < cur_str.size() ; i++) {
				if(isdigit(cur_str[i])) {
					point.add(cur_str[i]);
				}
			}

			out << cur_str<< " - ";
			if(point.isEmpty()) {
				out << "No Digit heare";
			}
			while(!point.isEmpty()) {
				out << point.pop();
			}
			out << std::endl;
		}

		std::cout << "Work is Done" << std::endl;
	}
	return 0;
}
