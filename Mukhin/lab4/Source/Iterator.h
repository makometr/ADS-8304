#ifndef ITERATOR
#define ITERATOR
#include "Tree.h"

class Node;

class TreeIterator {
public:
    virtual bool has_next() = 0;
    virtual Node* next() = 0;
};

class TreeIteratorDFS : public TreeIterator {
    private:
        unsigned int size = 0;
        std::vector<Node*> path_in_dip;
        void go_in_dip(Node*);
    public:
        explicit TreeIteratorDFS(Node* root);

        bool has_next() override;
        Node* next() override;

        ~TreeIteratorDFS() = default;
};

class TreeIteratorBFS : public TreeIterator {
    private:
        unsigned int size = 0;
        std::map<Node*, bool> is_visit;
        std::vector<Node*> path_in_breadth;
    public:
        explicit TreeIteratorBFS(Node* root);

        bool has_next() override ;
        Node* next() override;

        ~TreeIteratorBFS() = default;
};
#endif