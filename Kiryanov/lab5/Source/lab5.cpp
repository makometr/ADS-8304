#include <iostream>
#include <string>
#include <fstream>
#include <vector>
#include <ctime>
#include <memory>
#include <climits>
#include <istream>

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
	static bool check_rep(nodePtr<elem, priority>& t, elem key) {
		bool result = true;
		if (t->key == key)
			return false;
		else
			result=check_rep(key < t->key ? t->left : t->right, key);
		return result;
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
void dialog(nodePtr<elem, priority>& head) {
	int flag=0;
	std::cin >> flag;
	nodePtr<int, int> new_el = std::make_shared<Node<int, int>>();
	switch (flag){
	case(1):
		std::cout << "Please, enter a key" << std::endl;
		std::cin >> new_el->key;
		new_el->prior = rand() % INT_MAX;
		Node<int, int>::insert(head, new_el);
		printtree(head);
		std::cout << std::endl;
		std::cout << "Do you want to insert another one?" << std::endl << "Please, enter." << std::endl;
		std::cout << "'1' - Yes" << std::endl << "'2' - No" << std::endl;
		dialog(head);
		break;
	case(2):
		break;
	default:
		std::cout << "Wrong symbol, please enter again" << std::endl;
		dialog(head);
		break;
	}
}
template<typename elem, typename priority>
void printtree(nodePtr<elem, priority>& head) {
	if (!head) {
		std::cout << '#';
		return;
	}
	std::cout << '(';
	std::cout<< "(" << head->key << ";" << head->prior<<")";
	printtree(head->left);
	printtree(head->right);
	std::cout << ')';
}

int main(int argc, char* argv[]) {
	std::string array;
	if (argc == 1) {
		std::getline(std::cin, array);
		std::vector<nodePtr<int, int>> mypairs;
		create_int_vec(mypairs, array);
		for (unsigned long int i = 0; i < mypairs.size(); i++) {
			std::cout << mypairs[i]->key << ' ' << mypairs[i]->prior << std::endl;
		}
		nodePtr<int, int> head = nullptr;
		for (size_t i = 0; i < mypairs.size(); ++i){
			Node<int, int>::insert(head, mypairs[i]);
		}
		printtree(head);
		std::cout << std::endl;
		std::cout << "Do you want to insert new element?" << std::endl << "Please, enter." << std::endl;
		std::cout << "'1' - Yes" << std::endl << "'2' - No" << std::endl;
		dialog(head);
		printtree(head);
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
			for (unsigned long int i = 0; i < mypairs.size(); i++) {
				std::cout << mypairs[i]->key << ' ' << mypairs[i]->prior << std::endl;
			}
			nodePtr<int, int> head = nullptr;
			for (size_t i = 0; i < mypairs.size(); ++i) {
				Node<int, int>::insert(head, mypairs[i]);
			}
			printtree(head);
			std::cout << std::endl;
			std::cout << "Do you want to insert new element?" << std::endl << "Please, enter." << std::endl;
			std::cout << "'1' - Yes" << std::endl << "'2' - No" << std::endl;
			dialog(head);
			printtree(head);
			std::cout << std::endl;
		}
		in.close();
	}
	return 0;
}