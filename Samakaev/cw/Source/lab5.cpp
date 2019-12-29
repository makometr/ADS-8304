#include "bin_tree.h"


template<typename T>
bool str_to_t(T& item) {
	std::string str;
	std::cin >> str;

	std::stringstream linestream(str);
	linestream >> item;

	char c;
	if ((!linestream) || (linestream >> c)) {
		std::cout << "input type is not allowed" << std::endl;
		return false;
	}

	return true;
}

template<typename T>
void dialogue(BinTree<T> tree) {

	char option;
	T unit;

	tree.printTree();

	std::cout << "to add element enter \"1\"\nto quit the dialogue enter any other character\n";

	option = getchar();
	getchar();
	switch (option){
	case '1':
		std::cout << "Enter element you want to insert" << std::endl;
		if(str_to_t(unit))
			tree.task(unit);
		getchar();
		dialogue(tree);
		break;
	default:
		break;
	}
}

template<typename T>
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
	
	while (getline(file, expression)) {
		std::vector<T> units;
		std::istringstream iss(expression);

		BinTree<T> tree;
		T unit;
		while (iss >> unit) {
			units.push_back(unit);
		}

		tree.fill_tree(units);

		std::cout << i << ": " << expression << std::endl;
		i++;

		dialogue<T>(tree);
	}
	
}

int main(int argc, char** argv) {

	if (argc == 1) {
		std::cout<<"Please check you entered test file name";
	}
	else file_input<double>(argv[1]);
}