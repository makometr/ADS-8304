#include <iostream>
#include <string>
#include <fstream>

class Stack {
private:
	char* mystack;
	unsigned int index;
	int* position;
public:
	Stack(unsigned int size) {
		mystack = new char[size];
		position = new int[size];
		index = 0;
	}
	void push(char element, int pos) {
		mystack[index] = element;
		position[index] = pos;
		index++;
	}
	char pop() {
		index--;
		return mystack[index];
	}
	bool isEmpty() {
		return (index == 0);
	}
	char top() {
		if (!isEmpty())
			return mystack[index - 1];
		else
			return '0';
	}
	int mistake() {
		return position[index - 1];
	}
	~Stack() {
		delete[] mystack;
		delete[] position;
	}
};

int check(std::string& array) {
	Stack object(array.length());
	for (unsigned int i = 0; i < array.length(); i++) {
		if ((array[i] == '(')
			|| (array[i] == '[')
			|| (array[i] == '{')) {
			object.push(array[i], i + 1);
		}
		else if (array[i] == ')') {
			if (object.top() == '(')
				object.pop();
			else
				return (i + 1);
		}
		else if (array[i] == ']') {
			if (object.top() == '[')
				object.pop();
			else
				return (i + 1);
		}
		else if (array[i] == '}') {
			if (object.top() == '{')
				object.pop();
			else
				return (i + 1);
		}
	}
	if (object.isEmpty())
		return 0;
	else
		return object.mistake();
}

int main(int argc, char* argv[]) {
	std::string array;
	if (argc == 1) {
		std::getline(std::cin, array);
		int result = check(array);
		if (result == 0)
			std::cout << "No one mistake" << std::endl;
		else
			std::cout << "There is a mistake on " << result << " place" << std::endl;
	}
	else {
		std::ifstream in(argv[1]);
		if (!in.is_open()) {
			std::cout << "Can't open file" << std::endl;
			return 0;
		}
		while (std::getline(in, array)) {
			std::cout << array << "\n";
			int result = check(array);
			if (result == 0)
				std::cout << "No one mistake" << std::endl;
			else
				std::cout << "There is a mistake on " << result << " place" << std::endl;
		}
		in.close();
	}
	return 0;
}

