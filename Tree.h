#pragma once
#include <memory>
#include <map>
#include <iostream>
#include <queue>
#include "Iter.h"

class TreeIter;

struct Node_of_tree{
    int value;
    std::shared_ptr<Node_of_tree> left_Node = nullptr;
    std::shared_ptr<Node_of_tree> right_Node = nullptr;
};

class Tree{
private:
    std::shared_ptr<Node_of_tree> Tree_root;
    void insert_elem(std::shared_ptr<Node_of_tree>&, int element);
    std::map<std::shared_ptr<Node_of_tree>, int> nodes_at_levels();
public:
    explicit Tree(int);

    std::shared_ptr<TreeIter> make_DFS_iter();
    std::shared_ptr<TreeIter> make_BFS_iter();

    void insert_elem(int element);
    void cout_tree();

    int dip_tree();
    void cout_leaves();
    int dip_of_tree();
    int nodes_at_level(int);
};
