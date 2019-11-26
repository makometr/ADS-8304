#pragma once
#include <random>

template <class Elem>
class RandomBinarySearchTree
{
private:
    struct Node
    {
        Elem element;
        std::shared_ptr<Node> left;
        std::shared_ptr<Node> right;
        int N;
        explicit Node (Elem value)
        {
            element = value,
            left = right = 0;
            N = 1;
        }
    };
    typedef std::shared_ptr<Node> link;
    link head;

    link search(link root, Elem value)
    {
        if (!root) return 0;
        if (value == root->element) return root;
        if (value < root->element) return search(root->left, value);
        else return search(root->right, value);
    }

    int getSize(link root)
    {
        if (!root) return 0;
        return root->N;
    }

    void fixN(link root)
    {
        root->N = getSize(root->left) + getSize(root->right) + 1;
    }

    link rotateRight(link root)
    {
        link tmp = root->left;
        if (!tmp) return root;
        root->left = tmp->right;
        tmp->right = root;
        tmp->N = root->N;
        fixN(root);
        return tmp;
    }

    link rotateLeft(link root)
    {
        link tmp = root->right;
        if (!tmp) return root;
        root->right = tmp->left;
        tmp->left = root;
        tmp->N = root->N;
        fixN(root);
        return tmp;
    }

    link insertRoot(link root, Elem value)
    {
        if (!root) return std::unique_ptr<Node>(new Node(value));
        if (root->element > value)
        {
            root->left = insertRoot(root->left, value);
            return rotateRight(root);
        }
        else
        {
            root->right = insertRoot(root->right, value);
            return rotateLeft(root);
        }
    }

    link insert(link root, Elem value)
    {
        if (!root) return std::unique_ptr<Node>(new Node(value));
        if (rand()%(root->N+1) == 0) return insertRoot(root, value);
        if (root->element > value) root->left = insert(root->left, value);
        else root->right = insert(root->right, value);
        fixN(root);
        return root;
    }

    void print(link root, int i){
        if (root->right != 0) print(root->right, i+1);
        for (int j = 0 ; j < i; ++j)
            std::cout << " - ";
        std::cout << "(" << root->element << ")" << std::endl;
        if (root->left != 0) print(root->left, i+1);
    }

public:
    RandomBinarySearchTree()
    {
        head = 0;
    }

    void searchAndInsertElement(Elem value)
    {
        if (!search(head, value)) head = insert(head, value);
        else std::cout << "Element " << value << " already exists" << std::endl;
    }

    void printTree(int i)
    {
        print(head, i);
    }
};
