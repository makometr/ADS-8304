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

	void addRoots(std::shared_ptr<Branch> temp, std::string s) {

		size_t bracket_cnter = 0;
		size_t i = 0;

		if (isalpha(s[0]) || isdigit(s[0])) {
			temp->root = s[i];
			return;
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

				addRoots(temp->left, s.substr(1, i - 1));

				addRoots(temp->right, s.substr(i + 1, s.length() - i - 1));

				return;
			}
		}
	}

	void fill_map(std::shared_ptr<Branch> temporary, size_t depth, std::map<size_t, std::string>& depth_root_map) {

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
		addRoots(head, s);

		fill_map(head, depth, depth_root_map);
		print_tree(depth_root_map);

		change_tree(head);

		depth_root_map.clear();

		fill_map(head, depth, depth_root_map);
		print_tree(depth_root_map);

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