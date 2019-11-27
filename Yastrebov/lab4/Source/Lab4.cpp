

#include <iostream>
#include <fstream>
#include "BinTree.hpp"

int main(int argc, char* argv[])
{
	BinTree<std::string> bTree;
	std::string input;

	if (argc == 1)
	{
		std::ifstream iStream("Tests/test.txt");
		std::string mode;

		while (std::getline(iStream, mode)) {

			std::getline(iStream, input);

			if (mode == "NLR")
				bTree.head = bTree.readTreeFromStringNLR(input, input.begin(), input.end());

			if (mode == "LNR")
				bTree.head = bTree.readTreeFromStringLNR(input, input.begin(), input.end());

			if (mode == "LRN")
				bTree.head = bTree.readTreeFromStringLRN(input, input.begin(), input.end());

			std::getline(iStream, mode);

			if (mode == "NLR")
				bTree.printTreeNLR(bTree.head);

			if (mode == "LNR")
				bTree.printTreeLNR(bTree.head);

			if (mode == "LRN")
				bTree.printTreeLRN(bTree.head);

			std::cout << std::endl;
		}
	}

	if (argc == 2)
	{
		std::ifstream iStream(argv[1]);

		std::string mode;

		while (std::getline(iStream, mode))
		{

			std::getline(iStream, input);

			if (mode == "NLR")
				bTree.head = bTree.readTreeFromStringNLR(input, input.begin(), input.end());

			if (mode == "LNR")
				bTree.head = bTree.readTreeFromStringLNR(input, input.begin(), input.end());

			if (mode == "LRN")
				bTree.head = bTree.readTreeFromStringLRN(input, input.begin(), input.end());

			std::getline(iStream, mode);

			if (mode == "NLR")
				bTree.printTreeNLR(bTree.head);

			if (mode == "LNR")
				bTree.printTreeLNR(bTree.head);

			if (mode == "LRN")
				bTree.printTreeLRN(bTree.head);

			std::cout << std::endl;
		}
	}
}


