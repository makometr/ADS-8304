#ifndef TREE
#define TREE
#include <iostream>
#include <map>
#include <queue>
#include "Iterator.h"

class TreeIterator;

struct Node{
    int data;
    Node* left = nullptr;
    Node* right = nullptr;
};

class Tree{
    private:
        Node* root;
        void insert(Node*&, int element);
        void clear(Node*);
        std::map<Node*, int> get_nodes_and_levels();
    public:
        explicit Tree(int);

        TreeIterator* make_iterator_DFS();
        TreeIterator* make_iterator_BFS();

        void insert(int element);
        void print_tree();

        int dip();
        void print_leaves();
        int tree_length();
        int count_nodes_in_level(int);

        ~Tree();
};

#endif
