#include "h_content.h"

int main(int argc, char* argv[])
{
	setlocale(LC_ALL, "Russian");

	std::vector<std::string> input_nodes;

	std::ifstream input;
	
	input.open(argv[1]);

	if (!input) {
		std::cout << "Couldn't open source file";
		exit(1);
	}

	char tmp;
	std::string processed_string = "";

	while (input.get(tmp))
	{
		if (tmp != '\n')
			processed_string += tmp;
		else {
			if (processed_string.size())
				input_nodes.push_back(processed_string);
			processed_string = "";
		}
	}

	input_nodes.push_back(processed_string);

	input.close();

	std::sort(input_nodes.begin(), input_nodes.end()); // иначе изначальное содержимое не выгрузить в список, ибо по условию
							   // задания для добавления X.a должен существовать X
 	h_content hList;
	hList.load_h_content(input_nodes);
	while (true) {
		std::cout << "______________________" << std::endl;
		std::cout << 
			"Choose action :\n1 : print\n2 : add\n3 : insert\n4 : normalize"
			<< std::endl;

		int action;

		std::cin >> action;
		std::cin.get();

		if (action == 1)
		{
			hList.print(hList.head, "");
		}

		if (action == 2) {
			std::cout << "enter new node" << std::endl;

			std::string tmp;

			std::getline(std::cin, tmp);

			if (!hList.add(tmp))
				std::cout << "Failed" << std::endl;
		}

		if (action == 3) {
			std::cout << "enter new node" << std::endl;

			std::string tmp;

			std::getline(std::cin, tmp);

			if (!hList.insert(tmp))
				std::cout << "Failed" << std::endl;
		}

		if (action == 4) {

			std::string start;

			std::cout << "where to start? press enter to normalize from head" << std::endl;

			std::getline(std::cin, start);

			bool recursive = false;

			std::cout << "recursive? 1 - yes, 0 - no" << std::endl;

			std::cin >> recursive;

			hList.normalize(start, recursive);
		}
	}
}

