
#include <iostream>
#include <fstream>
#include "Treap.hpp"
#include <vector>
#include <string>
#include <ctime>

template<typename elem, typename priority>
void printtree(nodePtr<elem, priority>& head) {
	if (!head) {
		std::cout << '#';
		return;
	}
	std::cout << '(';
	std::cout << "(" << head->key << ";" << head->prior << ")";
	printtree(head->left);
	printtree(head->right);
	std::cout << ')';
}

void createIntNodeVector(std::vector<nodePtr<int, int>>& pairs, std::string& input) {
	srand((unsigned int)time(0));
	
	size_t index = 0;

	while (input[index] == ' ')
		++index;

	while (index < input.length()) {

		auto element = std::make_shared<Node<int, int>>(std::stoi(input.substr(index)), rand() % INT_MAX);

		pairs.push_back(element);

		while (isdigit(input[index]))
			++index;
		while (input[index] == ' ')
			++index;
	}
}




int main(int argc, char* argv[]) {
	std::string input;

	if (argc == 2) {
		freopen(argv[1], "r", stdin);
	}
	std::getline(std::cin, input);

	//example for <int, int>

	std::vector<nodePtr<int, int>> pairs;
	createIntNodeVector(pairs, input);

	nodePtr<int, int> head = nullptr;

	for (size_t i = 0; i < pairs.size(); ++i)
	{
		Node<int, int>::insert(head, pairs[i]);
	}

	std::cout << "tree : " << std::endl;

	printtree(head);

	std::cout << std::endl << "Which elements to delete?" << std::endl;

	int tmp = 0;

	while (std::cin >> tmp) {
		if (Node<int, int>::erase(head, tmp)) {
			std::cout  << "found and removed " << tmp << std::endl;

			std::cout << "tree : " << std::endl;

			printtree(head);
		}

		else {
			std::cout << "didin't find " << tmp << std::endl;

			std::cout << "tree : " << std::endl;

			printtree(head);
		}

		if(head)
			std::cout << "What elements to delete?" << std::endl;
	}
	
	return 0;
}
