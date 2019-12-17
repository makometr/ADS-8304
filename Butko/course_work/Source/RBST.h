#pragma once
#include <random>
#include <cmath>

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
        if (!root)
        {
            std::cout << " * искомый ключ " << value << " не существует в дереве. *" << std::endl;
            return 0;
        }
        if (value == root->element)
        {
            std::cout << " * искомый ключ " << value << " найден в дереве. *" << std::endl;
            return root;
        }
        if (value < root->element)
        {
            std::cout << " * искомый ключ " << value << " меньше, чем ключ текущего узла " <<
            root->element << ", спускаемся на левое поддерево. *"<< std::endl;
            return search(root->left, value);
        }
        else
        {
            std::cout << " * искомый ключ " << value << " больше, чем ключ текущего узла " <<
            root->element << ", спускаемся на правое поддерево. *"<< std::endl;
            return search(root->right, value);
        }
    }

    int getSize(link root)
    {
        if (!root) return 0;
        return root->N;
    }

    void fixN(link root)
    {
        root->N = getSize(root->left) + getSize(root->right) + 1;
        std::cout << " * фиксируем размер дерева равный " << root->N << ". *" << std::endl;
    }

    link rotateRight(link root)
    {
        link tmp = root->left;
        if (!tmp) return root;
        root->left = tmp->right;
        tmp->right = root;
        tmp->N = root->N;
        fixN(root);
        std::cout << " * производим правую ротацию *" << std::endl;
        std::cout << " ** дерево до ротации: **" << std::endl;
        print(root, 0);
        std::cout << " ** дерево после ротации: **" << std::endl;
        print(tmp, 0);
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
        std::cout << " * производим левую ротацию *" << std::endl;
        std::cout << " ** дерево до ротации: **" << std::endl;
        print(root, 0);
        std::cout << " ** дерево после ротации: **" << std::endl;
        print(tmp, 0);
        return tmp;
    }

    link insertRoot(link root, Elem value)
    {
        if (!root)
        {
            std::cout << "Узел " << value << " подвешен." << std::endl;
            return std::unique_ptr<Node>(new Node(value));
        }
        if (root->element > value)
        {
            std::cout << " * добавляемый ключ " << value << " меньше, чем ключ текущего узла " <<
            root->element << ", спускаемся на левое поддерево и производим правую ротацию. *"<< std::endl;
            root->left = insertRoot(root->left, value);
            return rotateRight(root);
        }
        else
        {
            std::cout << " * добавляемый ключ " << value << " больше, чем ключ текущего узла " <<
            root->element << ", спускаемся на правое поддерево и производим левую ротацию. *"<< std::endl;
            root->right = insertRoot(root->right, value);
            return rotateLeft(root);
        }
    }

    link insert(link root, Elem value)
    {
        if (!root)
        {
            std::cout << "Узел " << value << " подвешен." << std::endl;
            return std::unique_ptr<Node>(new Node(value));
        }
        if (rand()%(root->N+1) == 0)
        {
            std::cout << " * добавляемый ключ " << value << " вставляется на место текущего корня " <<
                      root->element << " с вероятностью "<< 1.0 / (1.0 + (double)root->N) << ". *" << std::endl;
            return insertRoot(root, value);
        }
        if (root->element > value)
        {
            std::cout << " * добавляемый ключ " << value << " меньше, чем ключ текущего узла " <<
            root->element << ", спускаемся на левое поддерево с вероятностью " << (double)root->N / (1.0 + (double)root->N) << ". *" << std::endl;
            root->left = insert(root->left, value);
        }
        else
        {
            std::cout << " * добавляемый ключ " << value << " больше, чем ключ текущего узла " <<
            root->element << ", спускаемся на правое поддерево с вероятностью " << (double)root->N / (1.0 + (double)root->N) << ". *"<< std::endl;
            root->right = insert(root->right, value);
        }
        fixN(root);
        return root;
    }

    link merge(link left, link right)
    {
        if(!left) return right;
        if(!right) return left;
        if(rand()%(left->N + right->N) < left->N)
        {
            std::cout << " * корень " << left->element << " (левый) был выбран корнем нового дерева с вероятностью "
            << (double) left->N / (double)(left->N + right->N) << ". *" << std::endl;
            left->right = merge(left->right, right);
            fixN(left);
            return left;
        }
        else
        {
            std::cout << " * корень " << right->element << " (правый) был выбран корнем нового дерева с вероятностью "
            << (double) right->N / (double)(left->N + right->N) << ". *" << std::endl;
            right->left = merge(left, right->left);
            fixN(right);
            return right;
        }
    }

    link remove(link root, Elem value)
    {
        if(!root)
        {
            std::cout << " * удаляемый ключ " << value << " не существует в дереве. *" << std::endl;
            return root;
        }
        if(root->element == value)
        {
            std::cout << " * удаляемый ключ " << value << " найден в дереве, начинается процедура удаления. *" << std::endl;
            link tmp = merge(root->left, root->right);
            return tmp;
        }
        else if(value < root->element)
        {
            std::cout << " * удаляемый  ключ " << value << " меньше, чем ключ текущего узла " <<
                      root->element << ", спускаемся на левое поддерево. *"<< std::endl;
            root->left = remove(root->left, value);
        }
        else
        {
            std::cout << " * удаляемый  ключ " << value << " больше, чем ключ текущего узла " <<
                      root->element << ", спускаемся на правое поддерево. *"<< std::endl;
            root->right = remove(root->right, value);
        }
        return root;
    }

    void print(link root, int i)
    {
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
        std::cout << " * начинается поиск элемента " << value << " среди элементов РБДП *" << std::endl;
        if (!search(head, value))
        {
            std::cout << "Ключ " << value << " не был найден в дереве." << std::endl;
            std::cout << " * начинается вставка элемента " << value << " в РБДП *" << std::endl;
            head = insert(head, value);
        }
        else std::cout << "Ключ " << value << " уже существует в дереве." << std::endl;
    }

    void deleteElement(Elem value)
    {
        head = remove(head, value);
    }

    void printTree(int i)
    {
        if(!head) std::cout << "Дерево не существует." << std::endl;
        else print(head, i);
    }

};
