﻿#include <iostream>
#include <string>
#include <fstream>
#include <vector>
#include <ctime>
#include <memory>
#include <climits>
#define COUNT 10 

template<typename elem, typename priority>
class Node;
template<typename elem, typename priority>
using nodePtr = std::shared_ptr<Node<elem, priority>>;
template<typename elem, typename priority>
class Node {
public:
	elem key, prior;
	nodePtr<elem, priority> left, right = nullptr;
	Node() = default;
	~Node() = default;
	static void split(nodePtr<elem, priority> head, elem key, nodePtr<elem, priority>& left, nodePtr<elem, priority>& right) {
		if (!head) {
			left = nullptr;
			right = nullptr;
		}
		else if (key < head->key) {
			split(head->left, key, left, head->left);
			right = head;
		}
		else {
			split(head->right, key, head->right, right);
			left = head;
		}
	}
	static void insert(nodePtr<elem, priority>& t, nodePtr<elem, priority> it) {
		if (!t)
			t = it;
		else if (it->prior > t->prior) {
			split(t, it->key, it->left, it->right);
			t = it;
		}
		else
			insert(it->key < t->key ? t->left : t->right, it);
	}
	static void merge(nodePtr<elem, priority>& t, nodePtr<elem, priority> l, nodePtr<elem, priority> r) {
		if (!l || !r)
			t = l ? l : r;
		else if (l->prior > r->prior) {
			merge(l->right, l->right, r);
			t = l;
		}
		else {
			merge(r->left, l, r->left);
			t = r;
		}
	}
	static bool erase(nodePtr<elem, priority>& t, elem key) {
		if (!t)
			return false;
		if (t->key == key) {
			merge(t, t->left, t->right);

			return true;
		}
		return erase(key < t->key ? t->left : t->right, key);
	}
};

void create_int_vec(std::vector<nodePtr<int, int>>& mypairs, std::string& array){
	srand((unsigned int)time(0));
	unsigned long int index = 0;
	while (array[index] == ' ')
		++index;
	while (index != array.length()) {
		nodePtr<int, int> el = std::make_shared<Node<int, int>>();
		el->key = std::stoi(array.substr(index));
		el->prior = rand() % INT_MAX;
		mypairs.push_back(el);
		while (isdigit(array[index]))
			++index;
		while (array[index] == ' ')
			++index;
	}
}

template<typename elem, typename priority>
void dialog(nodePtr<elem, priority>& head, int flag) {
	if (flag==0)
		std::cin >> flag;
	nodePtr<int, int> new_el = std::make_shared<Node<int, int>>();
	elem element;
	switch (flag){
	case(1):
		std::cout << "Please, enter a key" << std::endl;
		std::cin >> new_el->key;
		new_el->prior = rand() % INT_MAX;
		Node<int, int>::insert(head, new_el);
		std::cout << "This is a tree after inserting new element:" << std::endl;
		printtree(head, 0);
		std::cout << std::endl;
		std::cout << "Do you want to use again one of these operations?" << std::endl << "Please, enter." << std::endl;
		std::cout << "'1' - Insert new element" << std::endl << "'2' - Erase old element" << std::endl << "'3' - Exit" << std::endl;
		dialog(head, 0);
		break;
	case(2):
		std::cout << "Please, enter a key" << std::endl;
		std::cin >> element;
		if (Node<int, int>::erase(head, element)) {
			std::cout << "This is a tree after erasing element:" << std::endl;
			printtree(head, 0);
			std::cout << std::endl;
		}
		else
			std::cout << "There is no written element." << std::endl;
		std::cout << "Do you want to use again one of these operations?" << std::endl << "Please, enter." << std::endl;
		std::cout << "'1' - Insert new element" << std::endl << "'2' - Erase old element" << std::endl << "'3' - Exit" << std::endl;
		dialog(head, 0);
		break;
	case(3):
		break;
	default:
		std::cout << "Wrong symbol, please enter again" << std::endl;
		dialog(head, 0);
		break;
	}
}
template<typename elem, typename priority>
void printtree(nodePtr<elem, priority>& root, int space) {
	if (root == nullptr)
		return;
	space += COUNT;
	printtree(root->right, space);
	std::cout << std::endl;
	for (int i = COUNT; i < space; i++)
		std::cout << " ";
	std::cout << "(" << root->key << ";" << root->prior << ")\n";
	printtree(root->left, space);
}

int main(int argc, char* argv[]) {
	std::cout << "Hello! Please enter elements of tree." << std::endl;
	std::string array;
	if (argc == 1) {
		std::getline(std::cin, array);
		std::vector<nodePtr<int, int>> mypairs;
		create_int_vec(mypairs, array);
		nodePtr<int, int> head = nullptr;
		for (size_t i = 0; i < mypairs.size(); ++i) {
			Node<int, int>::insert(head, mypairs[i]);
		}
		std::cout << "This is your written tree:" << std::endl;
		printtree(head, 0);
		std::cout << std::endl;
		std::cout << "What do you want to do with tree?" << std::endl << "Please, enter." << std::endl;
		std::cout << "'1' - Insert new element" << std::endl << "'2' - Erase old element" << std::endl << "'3' - Exit" << std::endl;
		dialog(head, 0);
		std::cout << "This is final variant of the tree:" << std::endl;
		printtree(head, 0);
		std::cout << std::endl;
	}
	else {
		std::ifstream in(argv[1]);
		if (!in.is_open()) {
			std::cout << "Can't open file" << std::endl;
			return 0;
		}
		while (std::getline(in, array)) {
			std::cout << array << "\n";
			std::vector<nodePtr<int, int>> mypairs;
			create_int_vec(mypairs, array);
			nodePtr<int, int> head = nullptr;
			for (size_t i = 0; i < mypairs.size(); ++i) {
				Node<int, int>::insert(head, mypairs[i]);
			}
			std::cout << "This is your written tree:" << std::endl;
			printtree(head, 0);
			std::cout << std::endl;
			std::cout << "What do you want to do with tree?" << std::endl << "Please, enter." << std::endl;
			std::cout << "'1' - Insert new element" << std::endl << "'2' - Erase old element" << std::endl << "'3' - Exit" << std::endl;
			dialog(head, 0);
			std::cout << "This is final variant of the tree:" << std::endl;
			printtree(head, 0);
			std::cout << std::endl;
		}
		in.close();
	}
	return 0;
}