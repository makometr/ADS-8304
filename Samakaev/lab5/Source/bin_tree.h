#pragma once
#include <iostream>
#include <fstream>
#include <string>
#include <cctype>
#include <algorithm>
#include <vector>
#include <sstream>
#include <cstdlib>
#include <map>
#include <stack>


template<typename T> 
struct Branch {
	Branch() = default;

	std::shared_ptr<T> root = nullptr;
	std::shared_ptr<Branch> left = nullptr;
	std::shared_ptr<Branch> right = nullptr;

};

template<typename T>
class BinTree {
public:
	BinTree() {
		head = std::make_shared<Branch<T>>();
	}

	bool unit_insist(T unit, std::shared_ptr<Branch<T>> temp) {
		if (!temp->root) {
			return 0;
		}

		if (*(temp->root) > unit) {
			if (!temp->left)
				return 0;
			return unit_insist(unit, temp->left);
		}

		else if (*(temp->root) < unit) {
			if (!temp->right)
				return 0;
			return unit_insist(unit, temp->right);
		}

		return 1;
	}

	void update_height(std::shared_ptr<Branch<T>> temp, size_t cur_height) {

		height = std::max(height, cur_height);

		if (temp->left)
			update_height(temp->left, cur_height + 1);
		if(temp->right)
			update_height(temp->right, cur_height + 1);
	}

	//returns TRUE if tree already has unit and FALSE if it has not 
	bool Random_add_root(T unit, std::shared_ptr<Branch<T>> temp) {

		if (!unit_insist(unit, head)) {
			size_t random_tree_number = rand() % (size + 2);

			if (random_tree_number == size + 1) {

				if (!temp->root) {
					temp->root = std::make_shared<T>();
					*(temp->root) = unit;
					size++;
					return false;
				}

				if (*(temp->root) > unit) {
					std::shared_ptr<Branch<T>> new_head;

					new_head = std::make_shared<Branch<T>>();
					new_head->right = head;
					new_head->root = std::make_shared<T>();
					*(new_head->root) = unit;

					head = new_head;
					size++;
				}
				else {
					std::shared_ptr<Branch<T>> new_head;

					new_head = std::make_shared<Branch<T>>();
					new_head->left = head;
					new_head->root = std::make_shared<T>();
					*(new_head->root) = unit;

					head = new_head;
					size++;
				}
			}
			else addRoot(unit, temp);

			return true;
		}
		else 
			return false;

	}

	bool addRoot(T unit, std::shared_ptr<Branch<T>> temp) {

		if (!temp->root) {
			temp->root = std::make_shared<T>();
			*(temp->root) = unit;
			size++;
			return false;
		}

		if (*(temp->root) > unit) {
			if (!temp->left)
				temp->left = std::make_shared<Branch<T>>();
			return addRoot(unit, temp->left);
		}

		else if (*(temp->root) < unit) {
			if (!temp->right)
				temp->right = std::make_shared<Branch<T>>();
			return addRoot(unit, temp->right);
		}

		return true;
	}

	void fill_tree(std::vector<T> units) {

		for (size_t i = 0; i < units.size(); i++)
			Random_add_root(units.at(i), head);

		update_height(head, 1);
	}

	void task(T unit) {
		if (Random_add_root(unit, head))
			std::cout << "add element " << unit << std::endl;
		else std::cout << "stucture already has element "<< unit << std::endl;

		update_height(head, 1);
	}

	void printTree()
	{
		image.clear();

		std::string line(std::pow(2, height + 1) * 2, ' ');

		std::stack<std::shared_ptr<Branch<T> > > st;
		st.push(head);
		size_t cur_height = 0;

		while (cur_height != height)
		{
			std::vector<std::shared_ptr<Branch<T> > > nodes;
			size_t step = std::pow(2, height - cur_height + 1);
			size_t ind = std::pow(2, height - cur_height);

			while (!st.empty())
			{
				std::shared_ptr<Branch<T>> insertElem = st.top();
				st.pop();
				if (typeid(T) == typeid('c') && insertElem) {
					line.insert(ind, 1, *(insertElem->root));
				}
				else if (insertElem)
					line.insert(ind, std::to_string((*(insertElem->root))));
				else line.insert(ind, "#");
				ind += step + 6;

				nodes.push_back(insertElem);
			}
			for (int i = nodes.size() - 1; i >= 0; --i)
			{
				if (nodes[i] == nullptr)
				{
					st.push(nullptr);
					st.push(nullptr);
					continue;
				}
				st.push(nodes[i]->right);
				st.push(nodes[i]->left);
			}
			image.push_back(line);

			std::fill(line.begin(), line.end(), ' ');

			++cur_height;
		}

		for (auto line : image) {
			std::cout << line << std::endl;
		}

	}

	std::shared_ptr<Branch<T>>getHead() {
		return head;
	}

private:
	std::shared_ptr<Branch<T>> head;
	size_t size = 0;
	size_t height = 0;
	std::vector<std::string> image;
};