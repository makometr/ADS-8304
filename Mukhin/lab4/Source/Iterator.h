#pragma once
#include <vector>
#include "Tree.h"
class Node;


class TreeIterator {
public:
    virtual bool has_next() = 0;
    virtual std::shared_ptr<Node> next() = 0;
};


class TreeIteratorDFS : public TreeIterator {
private:
    unsigned int size = 0;
    std::vector<std::shared_ptr<Node>> path_in_dip;
    void go_in_dip(std::shared_ptr<Node> a);
public:
    explicit TreeIteratorDFS(std::shared_ptr<Node> root);

    bool has_next() override;
    std::shared_ptr<Node> next() override;
};


class TreeIteratorBFS : public TreeIterator {
private:
    unsigned int size = 0;
    std::map<std::shared_ptr<Node>, bool> is_visit;
    std::vector<std::shared_ptr<Node>> path_in_breadth;
public:
    explicit TreeIteratorBFS(std::shared_ptr<Node> root);

    bool has_next() override ;
    std::shared_ptr<Node> next() override;
};
