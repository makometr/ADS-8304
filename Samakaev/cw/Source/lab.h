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

	void fill_map(std::shared_ptr<Branch<T>> temporary, size_t depth, std::map<size_t, std::string>& depth_root_map) {

		depth++;

		/*if (!temporary->left && !temporary->right) {
			if (depth_root_map.find(depth) != depth_root_map.end())
				depth_root_map[depth] += std::to_string(*(temporary->root));
			else depth_root_map.insert(std::make_pair(depth, std::to_string(*(temporary->root))));
			return;
		}*/
		if (temporary->left)
			fill_map(temporary->left, depth, depth_root_map);
		else depth_root_map[depth + 1] += "     ";
		if(temporary->right)
			fill_map(temporary->right, depth, depth_root_map);
		else depth_root_map[depth + 1] += "     ";

		if ((depth_root_map.find(depth) != depth_root_map.end()) && (temporary->root))
			depth_root_map[depth] += std::to_string(*(temporary->root)) + "     ";
		else if (temporary->root) {
			depth_root_map.insert(make_pair(depth, std::to_string(*(temporary->root))));
			depth_root_map[depth] += "     ";
		}
	}

	
	void beauty_print_tree(std::map<size_t, std::string>& depth_root_map) {
		size_t j = 0;
		for (auto it = depth_root_map.begin(); it != depth_root_map.end(); it++) {
			for (int i = 0; i < depth_root_map.size() - j; i++)
				std::cout << "    ";
			std::cout << it->second << std::endl;
			j++;
		}
	}

	//возвращает количество успешно добавленных элементов
	void fill_tree(std::vector<T> numbers) {

		for (size_t i = 0; i < numbers.size(); i++)
			Random_add_root(numbers.at(i), head);
		size++;
	}

	void task(T unit) {
		if (Random_add_root(unit, head))
			std::cout << "add element " << unit << std::endl;
		else std::cout << "stucture already has element "<< unit << std::endl;
	}

	void print_tree() {

	/*	if(temp->root)
			std::cout << *(temp->root) << std::endl;
		if (temp->left)
			print_tree(temp->left);
		if(temp->right)
			print_tree(temp->right);*/
		fill_map(head, 0, depth_root_map);
		beauty_print_tree(depth_root_map);
		depth_root_map.clear();
	}

	std::shared_ptr<Branch<T>>getHead() {
		return head;
	}

private:
	std::shared_ptr<Branch<T>> head;
	size_t size = 0;
	std::map<size_t, std::string> depth_root_map;
};