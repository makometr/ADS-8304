#include <iostream>
#include <regex>
#include <string>
#include <fstream>
#include <variant>
#include <map>


struct Node {
	Node() = default;

	std::variant<char, int> value;
	std::variant<std::pair<Node*, Node*>, Node*> arguments;

	int calculate();

};

bool rec_fill_branch(Node*& element, std::string& expression);

void rec_free(Node*& head) {
	if (std::holds_alternative<std::pair<Node*, Node*>>(head->arguments)) {
		if ((std::get<std::pair<Node*, Node*>>(head->arguments).first))
			rec_free((std::get<std::pair<Node*, Node*>>(head->arguments).first));
		if ((std::get<std::pair<Node*, Node*>>(head->arguments).second))
			rec_free((std::get<std::pair<Node*, Node*>>(head->arguments).second));
		delete head;
	}
	else if (std::holds_alternative <Node*>(head->arguments)) {
		rec_free(std::get<Node*>(head->arguments));
		delete head;
	}
}

int Node::calculate()
{
	int devider;
	if (std::holds_alternative<char>(value))
	{
		if (std::get<char>(value) == '+')
			return std::get<std::pair<Node*, Node*>>(arguments).first->calculate() +
			std::get<std::pair<Node*, Node*>>(arguments).second->calculate();
		if (std::get<char>(value) == '*')
			return std::get<std::pair<Node*, Node*>>(arguments).first->calculate() *
			std::get<std::pair<Node*, Node*>>(arguments).second->calculate();
		if (std::get<char>(value) == '-')
		{
			if (std::holds_alternative<std::pair<Node*, Node*>>(arguments))
				return std::get<std::pair<Node*, Node*>>(arguments).first->calculate() -
				std::get<std::pair<Node*, Node*>>(arguments).second->calculate();
			else
				return (-1) * std::get<Node*>(arguments)->calculate();
		}
		if (std::get<char>(value) == '/') {
			devider = std::get<std::pair<Node*, Node*>>(arguments).second->calculate();
			if (devider != 0)
				return std::get<std::pair<Node*, Node*>>(arguments).first->calculate() / devider;
			else {
				throw(0);
			}
		}
	}
	else
		return std::get<int>(value);
	return 0;
}

bool is_operand(char c) {
	if (c == '-' || c == '+' || c == '*' || c == '/')
		return true;
	else return false;
}

void rec_cross(Node* element, int& i) {
	if (std::holds_alternative<char>(element->value) && std::holds_alternative<std::pair<Node*, Node*>>(element->arguments)) {
		if ((std::get<std::pair<Node*, Node*>>(element->arguments).first)) {
			if (std::get<char>(element->value)) {
				rec_cross((std::get<std::pair<Node*, Node*>>(element->arguments).first), i);
			}
		}
		if ((std::get<std::pair<Node*, Node*>>(element->arguments).second)) {
			if (std::get<char>(element->value)) {
				rec_cross((std::get<std::pair<Node*, Node*>>(element->arguments).second), i);
			}
		}
		i += 3;
	}
	else if (std::holds_alternative<char>(element->value) && std::holds_alternative<Node*>(element->arguments)) {
		if ((std::get<Node*>(element->arguments))) {
			if (std::get<char>(element->value)) {
				rec_cross(std::get<Node*>(element->arguments), i);
			}
		}
		i += 2;
	}

}

bool create_node(std::string& expression, int& i, Node*& element) {

	int bracket_cnt = 0;
	bool is_first = true;
	std::string buff;

	if (expression[i] == '(') {
		while (true) {
			buff += expression[i];
			if (expression[i] == '(') {
				bracket_cnt++;
			}
			else if (expression[i] == ')') {
				bracket_cnt--;
			}
			i++;
			if (bracket_cnt == 0) {
				break;
			}
		}

		if (!rec_fill_branch(element, buff))
			return false;
	}
	else {
		while (expression[i] != ' ' && expression[i] != '(' && expression[i] != ')') {
			if (isdigit(expression[i]) || (expression[i] == '-' && is_first)) {
				is_first = false;
				buff += expression[i];
				i++;
			}
			else
				return false;
		}
		element->value = stoi(buff);
		is_first = true;
	}

	return true;
}

bool rec_fill_branch(Node*& element, std::string& expression) {

	int i = 1;
	std::string buff;

	Node* left = new Node;
	bool f = create_node(expression, i, left);

	if (!f) {
		return false;
	}

	while (expression[i] == ' ') {
		i++;
	}

	if (is_operand(expression[i])) {
		if (expression[i] != '-')
			return false;
		else {
			element->value = expression[i];
			element->arguments = left;
			return true;
		}
	}

	else {
		Node* right = new Node;
		f = create_node(expression, i, right);

		if (!f) {
			return false;
		}

		while (expression[i] == ' ') {
			i++;
		}

		if (is_operand(expression[i]))
			element->value = expression[i];
		else
			return false;

		element->arguments = std::make_pair(left, right);
		return true;
	}

	return true;
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

void fill_map(std::string& values_str, std::map<std::string, int>& arguements_values_map) {

	std::regex pattern("(\\((\\w+) (-?\\d+)\\))");
	std::smatch match;

	int is_like_pattern = std::regex_search(values_str, match, pattern);
	while (is_like_pattern) {
		arguements_values_map.insert(std::pair<std::string, int>(match[2].str(), stoi(match[3])));
		values_str.erase(match.position(2), match[2].length());
		is_like_pattern = std::regex_search(values_str, match, pattern);
	}


	for (size_t i = 0; i < values_str.length(); i++) {
		if (isalpha(values_str[i])) {
			std::cout << "Incorrect arguement value!" << std::endl;
			break;
		}
	}
}

//replace var names with their values
bool substitute(std::string& expression, std::map<std::string, int>& arguements_values_map) {

	int pos = 0;
	std::string buff;
	for (auto it = arguements_values_map.begin(); it != arguements_values_map.end(); ++it) {
		buff = std::to_string(it->second);
		pos = expression.find(it->first);
		while (pos != -1) {
			if ((pos == 0 || !isalpha(expression[pos - 1])) && !isalpha(expression[pos + it->first.length()])) {
				expression.replace(pos, it->first.length(), buff);
				pos = expression.find(it->first, pos);
			}
			else pos = expression.find(it->first, pos + 1);
		}
	}

	arguements_values_map.clear();

	for (size_t i = 0; i < expression.length(); i++) {
		if (isalpha(expression[i])) {
			std::cout << "You didn't set all values" << std::endl;
			return false;
		}
	}

	return true;

}

void console_input(std::map <std::string, int>& arguements_values_map, Node* head) {

	std::cout << "Please enter an expression" << std::endl;
	std::string expression;

	getline(std::cin, expression);

	std::cout << "Please enter the values" << std::endl;
	std::string values;

	getline(std::cin, values);

	fill_map(values, arguements_values_map);
	int j = 0;
	if (is_brackets_correct(expression)) {
		if (substitute(expression, arguements_values_map)) {
			if (rec_fill_branch(head, expression)) {
				try {
					std::cout << head->calculate() << std::endl;
					rec_cross(head, j);
				}
				catch (int error) {
					if (error == 0)
						std::cout << "Division by zero was detected" << std::endl;
				}
			}
			else
				std::cout << expression << std::endl << "Incorrect expression detected" << std::endl;
		}
	}
}

void file_input(char* argv, std::map <std::string, int>& arguements_values_map, Node* head) {

	std::ifstream file;
	std::string file_name = argv;

	file.open(file_name);
	if (!file.is_open())
		std::cout << "Error! File isn't open" << std::endl;

	std::string expression;
	std::string values;
	int i = 0;
	while (!file.eof()) {
		i++;
		getline(file, expression);
		getline(file, values);

		int j = 0;

		std::cout << i << " : " << expression << std::endl << values << std::endl;

		fill_map(values, arguements_values_map);

		if (is_brackets_correct(expression)) {
			if (substitute(expression, arguements_values_map)) {
				if (rec_fill_branch(head, expression)) {
					try {
						std::cout << head->calculate() << std::endl;
						rec_cross(head, j);
						std::cout << j << std::endl;
					}
					catch (int error) {
						if (error == 0)
							std::cout << "Division by zero was detected" << std::endl;
					}
				}
				else
					std::cout << expression << std::endl << "Incorrect expression detected" << std::endl;
			}
		}
	}
}

int main(int argc, char** argv)
{
	Node* head = new Node;

	std::map <std::string, int> arguements_values_map;

	if (argc == 1)
		console_input(arguements_values_map, head);
	else if (argc == 2)
		file_input(argv[1], arguements_values_map, head);
	else std::cout << "Please check arguments are correct";

	rec_free(head);
}
}
