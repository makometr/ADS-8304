#include <iostream>
#include <regex>
#include <string>
#include <fstream>
#include <map>


bool is_brackets_correct(std::string &expression) {
	
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

	int is_like_pattern = 0;
	while (is_like_pattern = std::regex_search(values_str, match, pattern)) {
		arguements_values_map.insert(std::pair<std::string, int>(match[2].str(), stoi(match[3])));
		values_str.erase(match.position(2), match[2].length());
	}

	std::cout << "Arguements values" << std::endl;

	for (size_t i = 0; i < values_str.length(); i++) {
		if (isalpha(values_str[i])) {
			std::cout << "Incorrect arguement value!" << std::endl;
			break;
		}
	}

	for (auto it = arguements_values_map.begin(); it != arguements_values_map.end(); ++it) {
		std::cout << it->first << " = " << it->second << std::endl;
	}
}

void reg_calc(std::string& expression) {
	//group №         0,1,2     3,4          5   6,7      8         9        10         11
	std::regex patt("\\((( ){0,}((\\-)?\\d+)( )+)(( ){0,}(\\-?\\d+)( )+){0,}([\\-+*\\/])( ){0,}\\)");

	std::smatch match;
	int is_like_pattern = 0;
	int calc_res = 0;
	bool is_binary = false;
	int space_index = -1;

	std::cout << "Calculation:" << std::endl;
	while (is_like_pattern = std::regex_search(expression, match, patt)) {
		
		std::string str_to_insert;
		if (match[10] == '+') {
			std::cout << expression << std::endl;
			if (!match[6].matched) {
				str_to_insert = " " + match[3].str() + " ";
				expression.replace(match.position(0), match[0].length(), str_to_insert);
			}
			else {
				calc_res = stoi(match[3]) + stoi(match[8]);
				str_to_insert = " " + std::to_string(calc_res) + " ";
				expression.erase(match.position(8), match[8].length());
				expression.replace(match.position(1), match[1].length(), str_to_insert);
			}
		}
		else if (match[10] == '-') {
			std::cout << expression << std::endl;
			if (!match[6].matched) {
				str_to_insert = " " + match[3].str() + " ";
				expression.replace(match.position(0), match[0].length(), str_to_insert);
				if (!is_binary) {
					if (match[4].matched)
						expression.erase(match.position(4) - 1, 1);
					else
						expression.insert(match.position(3), "-");
				}
				is_binary = true;
			}
			else {
				calc_res = stoi(match[3]) - stoi(match[8]);
				str_to_insert = " " + std::to_string(calc_res) + " ";
				expression.erase(match.position(8), match[8].length());
				expression.replace(match.position(1), match[1].length(), str_to_insert);
				is_binary = true;
			}
		}
		else if (match[10] == '*') {
			std::cout << expression << std::endl;
			if (!match[6].matched) {
				str_to_insert = " " + match[3].str() + " ";
				expression.replace(match.position(0), match[0].length(), str_to_insert);
			}
			else {
				calc_res = stoi(match[3]) * stoi(match[8]);
				str_to_insert = " " + std::to_string(calc_res) + " ";
				expression.erase(match.position(8), match[8].length());
				expression.replace(match.position(1), match[1].length(), str_to_insert);
			}
		}
		else if (match[10] == '/') {
			std::cout << expression << std::endl;
			if (match[8].str() == "0")
				std::cout << "Devide by zero!" << std::endl;
			else {
				if (!match[6].matched) {
					str_to_insert = " " + match[3].str() + " ";
					expression.replace(match.position(0), match[0].length(), str_to_insert);
				}
				else {
					calc_res = stoi(match[3]) / stoi(match[8]);
					str_to_insert = " " + std::to_string(calc_res) + " ";
					expression.erase(match.position(8), match[8].length());
					expression.replace(match.position(1), match[1].length(), str_to_insert);
				}
			}
		}
	}

	space_index = expression.find(' ');
	while (space_index != -1) {
		expression.erase(space_index, 1);
		space_index = expression.find(' ');
	}

	std::cout << "Final reuslt is " << expression << std::endl;
}

//replace var names with their values
void substitute(std::string& expression, std::map<std::string, int>& arguements_values_map) {

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

	std::cout << "replaced variables with their values:" << std::endl << expression << std::endl;

	for (size_t i = 0; i < expression.length(); i++) {
		if (isalpha(expression[i])) {
			std::cout << "You didn't set all values" << std::endl;
			return;
		}
	}

}

void console_input(std::map <std::string, int>& arguements_values_map) {

	std::cout << "Please enter an expression" << std::endl;
	std::string expression;

	getline(std::cin, expression);

	std::cout << "Please enter the values" << std::endl;
	std::string values;

	getline(std::cin, values);

	fill_map(values, arguements_values_map);

	if (is_brackets_correct(expression)) {
		substitute(expression, arguements_values_map);
		reg_calc(expression);
	}

	std::cout << expression << std::endl;

}

void file_input(char* argv, std::map <std::string, int>& arguements_values_map) {

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

		std::cout << i << " : " << expression << std::endl << values << std::endl;

		fill_map(values, arguements_values_map);

		if (is_brackets_correct(expression)) {
			std::cout << expression << std::endl;
			substitute(expression, arguements_values_map);
			reg_calc(expression);
			std::cout << std::endl;
		}
	}
}

int main(int argc, char** argv)
{
	std::map <std::string, int> arguements_values_map;
	if (argc == 1)
		console_input(arguements_values_map);
	else if (argc == 2)
		file_input(argv[1], arguements_values_map);
	else std::cout << "Please check arguments are correct";
}
