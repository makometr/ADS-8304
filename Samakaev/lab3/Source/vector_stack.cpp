#include "vector_stack.h"


void fill_stack(Stack<char>& stack, std::string &str){

	for (size_t i = 0; i < str.length(); i++) {

		if (str[i] == '(' || str[i] == ')' || str[i] == ' ' || str[i] == ',')
			continue;
		else  stack.push(str[i]);
	}
}

void calculate(Stack<char>& stack, size_t depth) {

	if (stack.get_length() == 1 || stack.get_length() == 2)
		return;

	int right_arguement = stack.get_high();
	stack.pop();

	int left_arguement = stack.get_high();
	stack.pop();

	if (stack.get_high() == 'm') {
		
		stack.pop();

		if (stack.is_empty() || isdigit(stack.get_high())) {
			
			stack.push(std::min(left_arguement, right_arguement));
			
			calculate(stack, depth + 1);
		}
		else stack.push(std::min(left_arguement, right_arguement));

	}
	else if (stack.get_high() == 'M') {
		
		stack.pop();
		
		if (stack.get_length() == 0 || isdigit(stack.get_high())) {
			
			stack.push(std::max(left_arguement, right_arguement));
			
			calculate(stack, depth + 1);
		}
		else stack.push(std::max(left_arguement, right_arguement));
	}
	else {

		stack.push(left_arguement);
		
		calculate(stack, depth + 1);

		stack.push(right_arguement);

		calculate(stack, depth + 1);
	
	}
}

void file_input(char* &argv) {

	std::ifstream file;
	std::string testfile = argv;
	
	file.open(testfile);
	if (!file.is_open())
		std::cout << "Error! File isn't open" << std::endl;
	
	std::string str;
	
	while (!file.eof()) {
		
		Stack<char> stack;
		size_t depth = 0;
		
		getline(file, str);
		
		fill_stack(stack, str);
		try{
			calculate(stack, depth);
		}
		if (stack.get_length() == 1 && isdigit(stack.get_high()))
			std::cout << str << " = " << stack << std::endl;
		else std::cout << str << " is incorrect expression!" << std::endl;
	}
}

void console_input()
{
	Stack<char> stack;
	size_t depth = 0;

	std::string str;
	
	std::cout << "Enter the pattern to calculate" << std::endl;
	std::cin >> str;

	fill_stack(stack, str);
	try{
		calculate(stack, depth);
	}
	if (stack.get_length() == 1 && isdigit(stack.get_high()))
		std::cout << str << " = " << stack << std::endl;
	else std::cout << str << " is incorrect expression!" << std::endl;
}

//аргументом передаётся имя тестового файла
int main(int argc, char** argv)
{
	if (argc == 1)
		console_input();
	else if (argc == 2)
		file_input(argv[1]);
	else
		std::cout << "too much arguments" << std::endl;

	return 0;
}
