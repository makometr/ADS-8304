#include "lab.h"


void delete_space_symbols(std::string & expression) {
	expression.erase(std::remove_if(expression.begin(), expression.end(), &isspace), expression.end());
}

bool is_brackets_correct(std::string& expression) {

	int brackets_cnt = 0;

	for (size_t i = 0; i < expression.length(); i++) {
		if (brackets_cnt < 0)
			return false;
		else {
			if (expression[i] == '(')
				brackets_cnt++;
			else if (expression[i] == ')')
				brackets_cnt--;
			else continue;
		}
	}
	if (brackets_cnt == 0)
		return true;
	else return false;
}


void console_input() {
	BinTree tree;

	std::cout << "Please, enter the expression" << std::endl;
	std::string expression;

	getline(std::cin, expression);
	if (is_brackets_correct(expression)) {
		delete_space_symbols(expression);

		tree.replace_with_associative(expression);
	}
	else std::cout << "check if the brackets are correct" << std::endl;
}

void file_input(char* argv) {

	std::ifstream file;
	std::string testfile = argv;

	file.open(testfile);
	if (!file.is_open()) {
		std::cout << "Error! File isn't open" << std::endl;
		return;
	}
	
	size_t i = 1;

	std::string expression;

	while (!file.eof()) {

		BinTree tree;
		getline(file, expression);

		std::cout << i << ": " << expression << std::endl;
		if (is_brackets_correct(expression)) {

			delete_space_symbols(expression);

			tree.replace_with_associative(expression);

			std::cout << std::endl;
		}
		else std::cout << "check if the brackets are correct" << std::endl;
		i++;
	}
	
}

int main(int argc, char** argv) {

	if (argc == 1) {
		console_input();
	}
	else file_input(argv[1]);
}