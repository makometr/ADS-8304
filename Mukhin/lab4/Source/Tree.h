#pragma once
#include <memory>
#include <map>
#include <iostream>
#include <queue>
#include "Iterator.h"
class TreeIterator;
struct Node{
    int data;
    std::shared_ptr<Node> left = nullptr;
    std::shared_ptr<Node> right = nullptr;
};

class Tree{
private:
    std::shared_ptr<Node> root;
    void insert(std::shared_ptr<Node>&, int element);
    std::map<std::shared_ptr<Node>, int> get_nodes_and_levels();
public:
    explicit Tree(int);

    std::shared_ptr<TreeIterator> make_iterator_DFS();
    std::shared_ptr<TreeIterator> make_iterator_BFS();

    void insert(int element);
    void print_tree();

    int dip();
    void print_leaves();
    int tree_length();
    int count_nodes_in_level(int);
};
