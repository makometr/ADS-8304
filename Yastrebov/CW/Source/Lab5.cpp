
#include <iostream>
#include <fstream>
#include "Treap.hpp"
#include <vector>
#include <string>
#include <ctime>
#include <sstream>
#include <time.h>

#define TEST_SIZE 1000000
#define TEST_COUNT 5



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



int main(int argc, char* argv[]) {
	bool test(false);

	if ((argc == 2) && (*(argv[1]) == 't'))
		test = true;

	std::streambuf* backup;
	backup = std::cin.rdbuf();

	std::ifstream ifs;


	ifs.open("input.txt");

	std::cin.rdbuf(ifs.rdbuf());


	nodePtr<int, int> head = nullptr;

	int value(0);

	srand((unsigned int)time(0));

	if (!test)
		while (std::cin >> value)
		{
			if (!Node<int, int>::search(head, value))
				Node<int, int>::insert(head, std::make_shared<Node<int, int>>(value, rand() % INT_MAX));
			else
				std::cout << "Already there" << std::endl;
		}

	std::cin.rdbuf(backup);


	if (!test) {
		std::cout << "tree : " << std::endl;

		printtree(head);
		std::cout << std::endl;
	}


	for (bool f(1); f && !test; ) {
		std::cout << "Choose action :\n1 - insert\n2 - erase\n3 - exit" << std::endl;

		int action(0);
		std::cin >> action;

		switch (action) {
		case 1:
			std::cout << "Enter value" << std::endl;

			std::cin >> value;


			if (!Node<int, int>::search(head, value))
				Node<int, int>::insert(head, std::make_shared<Node<int, int>>(value, rand() % INT_MAX));
			else
				std::cout << "Already there" << std::endl;

			printtree(head);
			std::cout << std::endl;

			break;

		case 2:
			std::cout << "Enter value" << std::endl;

			std::cin >> value;

			Node<int, int>::erase(head, value);

			printtree(head);
			std::cout << std::endl;

			break;

		case 3:
			return 0;

		default:
			f = !f;
			break;
		}
	}




	for (int size = 10; size <= TEST_SIZE; size *= 10) {
		int maxDepth(0), avgDepth(0), maxInsertCalls(0), avgInsertCalls(0), maxEraseCalls(0), avgEraseCalls(0);

		std::cout << "\n_________________________AVERAGE TESTS_______________________\n";
		std::cout << "Size of treap : " << size << std::endl;

		for (int j = 0; j < TEST_COUNT; j++) {
			nodePtr<int, int> testHead = nullptr;

			int toBeSkipped = rand() % size;

			for (int i = 0; i < size; ++i)
			{
				if (i != toBeSkipped)
					Node<int, int>::insert(testHead, std::make_shared<Node<int, int>>(i, rand() % INT_MAX));
				else
					Node<int, int>::insert(testHead, std::make_shared<Node<int, int>>(size + 1, rand() % INT_MAX));

			}

			int tmp = Node<int, int>::depth(testHead);
			avgDepth += tmp;

			if (tmp > maxDepth)
				maxDepth = tmp;

			std::cout << "\nDepth : " << tmp << std::endl;

			counter = 0;



			std::cout << "\nInserting : " << toBeSkipped << std::endl;

			Node<int, int>::insert(testHead, std::make_shared<Node<int, int>>(toBeSkipped, rand() % INT_MAX));


			avgInsertCalls += counter;

			if (counter > maxInsertCalls)
				maxInsertCalls = counter;

			std::cout << "\nCalls : " << counter << std::endl;

			counter = 0;

			///

			tmp = rand() % size;
			std::cout << "\nErasing : " << tmp << std::endl;

			Node<int, int>::erase(testHead, tmp);


			avgEraseCalls += counter;

			if (counter > maxEraseCalls)
				maxEraseCalls = counter;

			std::cout << "\nCalls : " << counter << std::endl;

			counter = 0;


		}

		std::cout << "\nTests passed : " << TEST_COUNT << "\nmax depth : " << maxDepth << "\navg depth : " << avgDepth / TEST_COUNT << "\nmax insert calls : " << maxInsertCalls << "\navg insert calls : " << avgInsertCalls / TEST_COUNT
			<< "\nmax erase calls : " << maxEraseCalls << "\navg erase calls : " << avgEraseCalls / TEST_COUNT;
	}


	for (int size = 10; size <= TEST_SIZE; size *= 10) {
		int maxDepth(0), avgDepth(0), maxInsertCalls(0), avgInsertCalls(0), maxEraseCalls(0), avgEraseCalls(0);

		std::cout << "\n________________________WORST CASE TESTS_______________________\n";
		std::cout << "Size of treap : " << size << std::endl;

		for (int j = 0; j < TEST_COUNT; j++) {
			nodePtr<int, int> testHead = nullptr;

			int toBeSkipped = rand() % size;

			for (int i = 0; i < size; ++i)
			{
				if (i != toBeSkipped)
					Node<int, int>::insert(testHead, std::make_shared<Node<int, int>>(i, i));
				else
					Node<int, int>::insert(testHead, std::make_shared<Node<int, int>>(size + 1, size + 1));
			}

			int tmp = Node<int, int>::depth(testHead);
			avgDepth += tmp;

			if (tmp > maxDepth)
				maxDepth = tmp;

			std::cout << "\nDepth : " << tmp << std::endl;

			counter = 0;



			std::cout << "\nInserting : " << toBeSkipped << std::endl;

			Node<int, int>::insert(testHead, std::make_shared<Node<int, int>>(toBeSkipped, toBeSkipped));


			avgInsertCalls += counter;

			if (counter > maxInsertCalls)
				maxInsertCalls = counter;

			std::cout << "\nCalls : " << counter << std::endl;

			counter = 0;

			///

			tmp = rand() % size;
			std::cout << "\nErasing : " << tmp << std::endl;

			Node<int, int>::erase(testHead, tmp);


			avgEraseCalls += counter;

			if (counter > maxEraseCalls)
				maxEraseCalls = counter;

			std::cout << "\nCalls : " << counter << std::endl;

			counter = 0;


		}

		std::cout << "\nTests passed : " << TEST_COUNT << "\nmax depth : " << maxDepth << "\navg depth : " << avgDepth / TEST_COUNT << "\nmax insert calls : " << maxInsertCalls << "\navg insert calls : " << avgInsertCalls / TEST_COUNT
			<< "\nmax erase calls : " << maxEraseCalls << "\navg erase calls : " << avgEraseCalls / TEST_COUNT;
	}

	return 0;
}

