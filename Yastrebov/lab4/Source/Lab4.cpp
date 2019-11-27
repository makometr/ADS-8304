

#include <iostream>
#include <fstream>
#include "BinTree.hpp"

int main(int argc, char* argv[])
{
	BinTree<std::string> bTree;
	std::string input;
	int test_cnt = 0;

	if (argc == 1)
	{
		std::ifstream iStream("test.txt");
		std::string mode;

		while (std::getline(iStream, mode)) {

			std::cout << "______________\ntest#" << test_cnt++ << std::endl;

			std::cout << "input in " << mode << std::endl;

			std::getline(iStream, input);

			std::cout << "input " << input << std::endl;

			if (mode == "NLR")
				bTree.head = bTree.readTreeFromStringNLR(input, input.begin(), input.end());

			if (mode == "LNR")
				bTree.head = bTree.readTreeFromStringLNR(input, input.begin(), input.end());

			if (mode == "LRN")
				bTree.head = bTree.readTreeFromStringLRN(input, input.begin(), input.end());

			std::getline(iStream, mode);

			if (mode == "NLR")
			{
				std::cout << "output in " << mode << std::endl;
				bTree.printTreeNLR(bTree.head);
			}

			if (mode == "LNR") {
				std::cout << "output in " << mode << std::endl;
				bTree.printTreeLNR(bTree.head);
			}

			if (mode == "LRN")
			{
				std::cout << "output in " << mode << std::endl;
				bTree.printTreeLRN(bTree.head);
			}

			std::cout << std::endl;

			print2D(bTree.head);
		}
	}

	if (argc == 2)
	{
		std::ifstream iStream;

		std::string mode;

		iStream.open(argv[1]);

		while (std::getline(iStream, mode))
		{
			std::cout << "test#" << test_cnt++ << std::endl;

			std::cout << "input in " << mode << std::endl;

			std::getline(iStream, input);

			std::cout << "input " << input << std::endl;

			if (mode == "NLR")
				bTree.head = bTree.readTreeFromStringNLR(input, input.begin(), input.end());

			if (mode == "LNR")
				bTree.head = bTree.readTreeFromStringLNR(input, input.begin(), input.end());

			if (mode == "LRN")
				bTree.head = bTree.readTreeFromStringLRN(input, input.begin(), input.end());

			std::getline(std::cin, mode);

			if (mode == "NLR")
			{
				std::cout << "output in " << mode << std::endl;
				bTree.printTreeNLR(bTree.head);
			}

			if (mode == "LNR")
			{
				std::cout << "output in " << mode << std::endl;
				bTree.printTreeLNR(bTree.head);
			}

			if (mode == "LRN")
			{
				std::cout << "output in " << mode << std::endl;
				bTree.printTreeLRN(bTree.head);
			}

			std::cout << std::endl;
		}
	}
}


