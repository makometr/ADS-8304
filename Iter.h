#pragma once
#include <vector>
#include "Tree.h"
class Node_of_tree;

class TreeIter {
public:
    virtual bool has_next() = 0;
    virtual std::shared_ptr<Node_of_tree> next() = 0;
};

class TreeIterBFS : public TreeIter {
private:
    unsigned int size = 0;
    std::map<std::shared_ptr<Node_of_tree>, bool> visiting;
    std::vector<std::shared_ptr<Node_of_tree>> breadth_path;
public:
    TreeIterBFS(const std::shared_ptr<Node_of_tree>& root);

    bool has_next();
    std::shared_ptr<Node_of_tree> next();
};

class TreeIterDFS : public TreeIter {
private:
    unsigned int size = 0;
    std::vector<std::shared_ptr<Node_of_tree>> dip_path;
    void go_in_dip(const std::shared_ptr<Node_of_tree>& a);
public:
    TreeIterDFS(const std::shared_ptr<Node_of_tree>& root);

    bool has_next();
    std::shared_ptr<Node_of_tree> next();
};
