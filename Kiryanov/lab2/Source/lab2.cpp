#include <iostream>
#include <string>
#include <stack>
#include <variant>
#include <fstream>

struct binkor {
	int lenght;
	std::variant<std::pair<binkor*, binkor*>, int> system;
	~binkor() {
		if (std::holds_alternative<std::pair<binkor*, binkor*>>(system)) {
			delete std::get<std::pair<binkor*, binkor*>>(system).first;
			delete std::get<std::pair<binkor*, binkor*>>(system).second;
		}
	}
};

bool check(std::string array) {
	std::stack <char> Stack;
	for (unsigned int i = 0; i < array.length(); i++) {
		if (array[i] == '(')
			Stack.push(array[i]);
		else if (array[i] == ')') {
			if (Stack.empty()) {
				return false;
			}
			Stack.pop();
		}
		else {
			if ((array[i] != ' ' && !isdigit(array[i]))
				|| Stack.empty()) {
				return false;
			}
		}
	}
	if (!Stack.empty()) {
		return false;
	}
	return true;
}
int read(std::string &array, long unsigned int index, binkor* kor) {
	std::pair<binkor*, binkor*> side;
	if (isdigit(array[index])) {
		kor->lenght = std::stoi(array.substr(index));
	}
	while (isdigit(array[index])){
		index++;
	}
	if (array[index] == ' ')
		index++;
	if (array[index] == '(') {
		binkor* left = new binkor;
		side.first = left;
		kor->system = side;
		while (array[index] == '(')
			index++;
		index=read(array, index, std::get<std::pair<binkor*,binkor*>>(kor->system).first);
	}
	else {
		kor->system = std::stoi(array.substr(index));
		while (isdigit(array[index])) {
			index++;
		}
	}
	if (array[index] == ' ')
		index++;
	if (array[index] == '(') {
		binkor* right = new binkor;
		side.second = right;
		kor->system = side;
		index++;
		index = read(array, index, std::get<std::pair<binkor*, binkor*>>(kor->system).second);
		if (index == array.length() - 1)
			return 0;
		else
			index++;
	}
	if (array[index] == ')') {
		index++;
		return index;
	}
	return 0;
}

int count(binkor* kor) {
	int result = 0;
	if (std::holds_alternative<std::pair<binkor*, binkor*>>(kor->system)) {
		result += count(std::get<std::pair<binkor*, binkor*>>(kor->system).first);
		result += count(std::get<std::pair<binkor*, binkor*>>(kor->system).second);
	}
	else {
		result++;
	}
	return result;
}

int stackcount(binkor* kor) {
	std::stack <binkor*> Stackich;
	int result = 0;
	while (1) {
		if (std::holds_alternative<std::pair<binkor*, binkor*>>(kor->system)) {
			Stackich.push(kor);
			kor = std::get<std::pair<binkor*, binkor*>>(kor->system).first;
		}
		else {
			result++;
			if (!Stackich.empty()) {
				kor = Stackich.top();
				Stackich.pop();
				kor = std::get<std::pair<binkor*, binkor*>>(kor->system).second;
			}
			else
				break;
		}
	}
	return result;
}

int main(int argc, char* argv[]){
	std::string array;
	if (argc == 1) {
		std::getline(std::cin, array);
		if (!check(array)) {
			std::cout << "Wrong input" << std::endl;
			return 0;
		}
		binkor* kor=new binkor;
		kor->lenght = 0;
		read(array, 0, kor);
		std::cout << count(kor) << std::endl;
		std::cout << stackcount(kor) << std::endl;
		delete kor;
	}
	else {
		std::ifstream in(argv[1]);
		if (!in.is_open()) {
			std::cout << "Can't open file" << std::endl;
			return 0;
		}
		while (std::getline(in, array)) {
			std::cout << array << "\n";
			if (!check(array)){
				std::cout << "Wrong input"<<std::endl;
			}
			else {
				binkor* kor;
				kor = new binkor;
				kor->lenght = 0;
				read(array, 0, kor);
				std::cout << count(kor) << std::endl;
				delete kor;
			}
		}
		in.close();
	}
	return 0;

}
