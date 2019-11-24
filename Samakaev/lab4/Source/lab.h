#pragma once
#include <iostream>
#include <fstream>
#include <string>
#include <cctype>
#include <map>
#include <algorithm>

struct Branch {
	Branch() = default;

	std::string root = "0";
	std::shared_ptr<Branch> left = nullptr;
	std::shared_ptr<Branch> right = nullptr;

};


class BinTree {
public:
	BinTree() {
		head = std::make_shared<Branch>();
	}

	bool iscorrect(std::string &s) {
		if ((s[0] != '(' || s[s.length() - 1] != ')') && s.length() != 1)
			return false;
		else return true;
	}


	bool addRoots(std::shared_ptr<Branch> temp, std::string s) {

		if (!iscorrect(s)) {
			return 0;
		}

		size_t bracket_cnter = 0;
		size_t i = 0;

		if (isalpha(s[0]) || isdigit(s[0])) {
			if (s.length() == 1) {
				temp->root = s[i];
				return 1;
			}
			else return 0;
		}

		for (size_t i = 0; i < s.length(); i++) {
			if (s[i] == '(') {
				bracket_cnter++;
			}
			else if (s[i] == ')') {
				bracket_cnter--;
			}

			if ((s[i] == '+' || s[i] == '-' || s[i] == '*') && bracket_cnter == 1) {

				temp->left = std::make_shared<Branch>();
				temp->right = std::make_shared<Branch>();

				temp->root = s[i];

				if (!addRoots(temp->left, s.substr(1, i - 1)))
					return 0;

				if(!addRoots(temp->right, s.substr(i + 1, s.length() - i - 2)))
					return 0;

				return 1;
			}
		}
		return 0;
	}

	void fill_map(std::shared_ptr<Branch> temporary, size_t depth, std::map<size_t, std::string> &depth_root_map) {

		depth++;

		if (!temporary->left || !temporary->right) {
			if (depth_root_map.find(depth) != depth_root_map.end())
				depth_root_map[depth] += temporary->root;
			else depth_root_map.insert(make_pair(depth, temporary->root));
			return;
		}
		
		fill_map(temporary->left, depth, depth_root_map);

		fill_map(temporary->right, depth, depth_root_map);
		
		if (depth_root_map.find(depth) != depth_root_map.end())
			depth_root_map[depth] += temporary->root;
		else depth_root_map.insert(make_pair(depth, temporary->root));
	}

	void print_tree(std::map<size_t, std::string>& depth_root_map) {
		for (auto it = depth_root_map.begin(); it != depth_root_map.end(); it++)
			std::cout << it->first << " " << it->second << std::endl;
	}

	void replace_with_associative(std::string s) {
		if (!addRoots(head, s)) {
			std::cout << "incorrect expression form" << std::endl;
			return;
		}

		fill_map(head, depth, depth_root_map);
		change_tree(head);
		std::cout << "expression after associative changes:\n" << make_infix_expression(head) << std::endl;
		depth_root_map.clear();

		std::cout << "prefix form:\n" << make_prefix_expression(head) << std::endl;
		std::cout << "infix form:\n" << make_suffix_expression(head) << std::endl;

	}

	
	std::string make_prefix_expression(std::shared_ptr<Branch> temporary) {
		if (!temporary->left || !temporary->right) {
			return temporary->root;
		}
		return "(" + temporary->root + " " + make_prefix_expression(temporary->left) + " " + make_prefix_expression(temporary->right) + ")";
	}

	std::string make_suffix_expression(std::shared_ptr<Branch> temporary) {
		if (!temporary->left || !temporary->right) {
			return temporary->root;
		}
		return "(" + make_suffix_expression(temporary->left) + " " + make_suffix_expression(temporary->right) + " " + temporary->root + ")";
	}

	std::string make_infix_expression(std::shared_ptr<Branch> temporary) {
		if (!temporary->left || !temporary->right) {
			return temporary->root;
		}
		return "(" + make_infix_expression(temporary->left) + " " + temporary->root + " " + make_infix_expression(temporary->right) + ")";
	}

	void change_tree(std::shared_ptr<Branch> temporary) {
		if (!temporary->left || !temporary->right) {
			return;
		}

		if (temporary->root == "*") {
			if (temporary->left->root == "+") {
				Branch buffer = *temporary->left->right;
				temporary->left->right = temporary->right;
				temporary->left->root = "*";
				temporary->root = "+";
				temporary->right = std::make_shared<Branch>();
				temporary->right->left = std::make_shared<Branch>();
				temporary->right->right = std::make_shared<Branch>();
				temporary->right->root = "*";
				*temporary->right->left = buffer;
				temporary->right->right = temporary->left->right;
			}
			else if (temporary->right->root == "+") {
				Branch buffer = *temporary->right->left;
				temporary->right->left = temporary->left;
				temporary->right->root = "*";
				temporary->root = "+";
				temporary->left = std::make_shared<Branch>();
				temporary->left->right = std::make_shared<Branch>();
				temporary->left->left = std::make_shared<Branch>();
				temporary->left->root = "*";
				*temporary->left->right = buffer;
				temporary->left->left = temporary->right->left;
			}
		}

		change_tree(temporary->left);
		change_tree(temporary->right);
	}

private:
	std::shared_ptr<Branch> head;
	std::map<size_t, std::string> depth_root_map;
	size_t depth = 0;
};