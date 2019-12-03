#include <iostream>
#include <string>
#include <stack>
#include <fstream>
#include <vector>
#include <algorithm>
#include <queue>
#define COUNT 10 

std::string::iterator find_end(std::string& str, std::string::iterator start){
	int cntr = 0;
	while (start < str.end()){
		if (*start == '(')
			++cntr;
		if (*start == ')')
			--cntr;
		if (!cntr)
			return start;
		++start;
	}
	return start;
}

template <typename type>
class Forest {
public:
	struct bintree {
		type value;
		bintree* right = nullptr;
		bintree* left = nullptr;
		~bintree() {
			delete right;
			delete left;
		}
	};
	struct tree {
		type value;
		std::vector <tree*> branches;
		~tree() {
			for (int i = 0; i < branches.size(); i++)
				delete branches[i];
		}
	};
	std::vector <tree*> forest;
	Forest() = default;
	Forest(const Forest<type>& copy) {
		for (int i = 0; i < (copy.forest).size(); ++i) {
			forest.push_back(copy.forest[i]);
		}

	}
	void input(std::string& array) {
		std::string::iterator start, end;
		start = array.begin();
		end = start;
		while (end != array.end() - 1) {
			end = find_end(array, start);
			forest.push_back(createtree(array, start, end));
			if (end != array.end() - 1)
				start = end + 1;
		}
	}

	tree* createtree(std::string& array, std::string::iterator start, std::string::iterator end) {
		tree* res = new tree;
		res->value = type(*(++start));
		++start;
		while (start <= end) {
			if (*start == ')')
				return res;
			if (*start == '(')
				res->branches.push_back(createtree(array, start, find_end(array, start)));
			start = find_end(array, start);
			if (start != array.end())
				++start;
		}
		return res;
	}
	void printforest(std::vector <tree*> forest) {
		std::queue<tree*> qu;
		for (long unsigned int i = 0; i < forest.size(); i++) {
			qu.push(forest[i]);
		}
		while (!qu.empty()) {
			std::cout << (qu.front())->value;
			for (long unsigned int i = 0; i < ((qu.front())->branches).size(); i++) {
				qu.push((qu.front())->branches[i]);
			}
			qu.pop();
		}
	}
	bintree* mybin = new bintree;
	void createbintree(std::vector <tree*> forest, bintree* mybin, long unsigned int index) {
		mybin->value = forest[index]->value;
		if ((forest[index]->branches).size() != 0) {
			mybin->left = new bintree;
			createbintree(forest[index]->branches, mybin->left, 0);
		}

		if (index != forest.size()-1) {
			mybin->right = new bintree;
			createbintree(forest, mybin->right, index+1);
		}
	}
	void printtree(bintree* mybin) {
		if (!mybin) {
			std::cout << '#';
			return;
		}
		std::cout << '(';
		std::cout << mybin->value;
		printtree(mybin->left);
		printtree(mybin->right);
		std::cout << ')';
	}
	void print2DUtil(bintree* root, int space){ 
		if (root == nullptr)
			return;
		space += COUNT;
		print2DUtil(root->right, space);
		std::cout << std::endl;
		for (int i = COUNT; i < space; i++)
			std::cout << " ";
		std::cout << root->value << "\n";
		print2DUtil(root->left, space);
	}
	void print2D(bintree* root){ 
		print2DUtil(root, 0);
	}

	~Forest() {
		delete mybin;
		for (int i = 0; i < forest.size(); i++)
			delete forest[i];
	}
};

bool check(std::string& array) {
	std::stack <char> Stack;
	for (unsigned int i = 0; i < array.length(); ++i) {
		if (array[i] == '(') {
			Stack.push(array[i]);
			if ((array[i + 1] == '(') || (array[i + 1] == ')'))
				return false;
		}
		else if (array[i] == ')') {
			if (Stack.empty()) {
				return false;
			}
			Stack.pop();
		}
		else {
			if (!Stack.empty()) {
				if (array[i - 1] != '(')
					return false;
				if ((array[i + 1] != '(') && (array[i + 1] != ')'))
					return false;
			}
			else
				if (array[i] != ' ')
					return false;
		}
	}
	if (!Stack.empty()) {
		return false;
	}
	return true;
}

int main(int argc, char* argv[]) {
	
	std::string array;
	if (argc == 1) {
		std::getline(std::cin, array);
		array.erase(std::remove(array.begin(), array.end(), ' '), array.end());
		if (!check(array)) {
			std::cout << "Wrong input" << std::endl;
			return 0;
		}
		std::cout << array << "\n";
		Forest<char>  myForest;
		myForest.input(array);
		myForest.printforest(myForest.forest);
		std::cout << std::endl;
		myForest.createbintree(myForest.forest, myForest.mybin, 0);
		myForest.printtree(myForest.mybin);
		myForest.print2D(myForest.mybin);
	}
	else {
		std::ifstream in(argv[1]);
		if (!in.is_open()) {
			std::cout << "Can't open file" << std::endl;
			return 0;
		}
		while (std::getline(in, array)) {
			if (!check(array)) {
				std::cout << "Wrong input" << std::endl;
				continue;
			}
			array.erase(std::remove(array.begin(), array.end(), ' '), array.end());
			std::cout << array << "\n";
			Forest<char>  myForest;
			myForest.input(array);
			myForest.printforest(myForest.forest);
			std::cout << std::endl;
			myForest.createbintree(myForest.forest, myForest.mybin, 0);
			myForest.printtree(myForest.mybin);
			myForest.print2D(myForest.mybin);
		}
		in.close();
	}
	return 0;
}
