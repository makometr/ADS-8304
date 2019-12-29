#ifndef avl_hpp
#define avl_hpp

#include <stdio.h>
#include <iostream>


/* AVL node */
template <class T>
class AVLnode {
    public:
        T key;
        int balance;
        AVLnode *left, *right, *parent;
     
        AVLnode(T k, AVLnode *p) :
                            key(k),
                            balance(0),
                            parent(p),
                            left(NULL), right(NULL) {}
        ~AVLnode() {
            delete left;
            delete right;
        }
    
};

/* AVL tree */
template <class T>
class AVLtree {
    public:
        AVLtree() = default;
        AVLtree(const AVLtree<T> &) = delete;
        ~AVLtree() {
            delete root;
        }
        AVLtree &operator=(const AVLtree<T> &) = delete;
    
        AVLnode<T> *root = nullptr;
        bool insert(T key);
        void deleteKey(const T key);
        void searchElem(T key,AVLnode<T> *root, bool &found);
        void bracketNotation(AVLnode<T>* root, std::string& str);
        void printBaracketNotation();
        int height(AVLnode<T> *n);

    private:
        AVLnode<T>* rotateLeft(AVLnode<T> *a);
        AVLnode<T>* rotateRight(AVLnode<T> *a);
        AVLnode<T>* rotateLeftThenRight(AVLnode<T> *n);
        AVLnode<T>* rotateRightThenLeft(AVLnode<T> *n);
        void rebalance(AVLnode<T> *n);
        void setBalance(AVLnode<T> *n);
};

#endif /* avl_hpp */

/* AVL class definition */

template <class T>
int AVLtree<T>::height(AVLnode<T> *n) {
    if (n == NULL)
        return -1;
    return 1 + std::max(height(n->left), height(n->right));
}
 
template <class T>
void AVLtree<T>::setBalance(AVLnode<T> *n) {
    n->balance = height(n->right) - height(n->left);
}


template <class T>
void AVLtree<T>::rebalance(AVLnode<T> *n) {
    setBalance(n);
 
    if (n->balance == -2) {
        if (height(n->left->left) >= height(n->left->right))
            n = rotateRight(n);
        else
            n = rotateLeftThenRight(n);
    }
    else if (n->balance == 2) {
        if (height(n->right->right) >= height(n->right->left))
            n = rotateLeft(n);
        else
            n = rotateRightThenLeft(n);
    }
 
    if (n->parent != NULL) {
        rebalance(n->parent);
    }
    else {
        root = n;
    }
}

template <class T>
bool AVLtree<T>::insert(T key) {
    if (root == NULL) {
        root = new AVLnode<T>(key, NULL);
    }
    else {
        AVLnode<T>
            *n = root,
            *parent;
 
        while (true) {
            if (n->key == key)
                return false;
 
            parent = n;
 
            bool goLeft = key < n->key;
            n = goLeft ? n->left : n->right;
 
            if (n == NULL) {
                if (goLeft) {
                    parent->left = new AVLnode<T>(key, parent);
                }
                else {
                    parent->right = new AVLnode<T>(key, parent);
                }
 
                rebalance(parent);
                break;
            }
        }
    }
    
    return true;
}
 
template <class T>
void AVLtree<T>::deleteKey(const T delKey) {
    if (root == NULL)
        return;
 
    AVLnode<T>
        *n       = root,
        *parent  = root,
        *delNode = NULL,
        *child   = root;
 
    while (child != NULL) {
        parent = n;
        n = child;
        child = delKey >= n->key ? n->right : n->left;
        if (delKey == n->key)
            delNode = n;
    }
 
    if (delNode != NULL) {
        delNode->key = n->key;
 
        child = n->left != NULL ? n->left : n->right;
 
        if (root->key == delKey) {
            root = child;
        }
        else {
            if (parent->left == n) {
                parent->left = child;
            }
            else {
                parent->right = child;
            }
 
            rebalance(parent);
        }
    }
}
 
 
template <class T>
AVLnode<T>* AVLtree<T>::rotateLeft(AVLnode<T> *a) {
    AVLnode<T> *b = a->right;
    b->parent = a->parent;
    a->right = b->left;
 
    if (a->right != NULL)
        a->right->parent = a;
 
    b->left = a;
    a->parent = b;
 
    if (b->parent != NULL) {
        if (b->parent->right == a) {
            b->parent->right = b;
        }
        else {
            b->parent->left = b;
        }
    }
 
    setBalance(a);
    setBalance(b);
    return b;
}
 
template <class T>
AVLnode<T>* AVLtree<T>::rotateRight(AVLnode<T> *a) {
    AVLnode<T> *b = a->left;
    b->parent = a->parent;
    a->left = b->right;
 
    if (a->left != NULL)
        a->left->parent = a;
 
    b->right = a;
    a->parent = b;
 
    if (b->parent != NULL) {
        if (b->parent->right == a) {
            b->parent->right = b;
        }
        else {
            b->parent->left = b;
        }
    }
 
    setBalance(a);
    setBalance(b);
    return b;
}
 
template <class T>
AVLnode<T>* AVLtree<T>::rotateLeftThenRight(AVLnode<T> *n) {
    n->left = rotateLeft(n->left);
    return rotateRight(n);
}
 
template <class T>
AVLnode<T>* AVLtree<T>::rotateRightThenLeft(AVLnode<T> *n) {
    n->right = rotateRight(n->right);
    return rotateLeft(n);
}

template <class T>
void AVLtree<T>::searchElem(T key,AVLnode<T> *root, bool &found){
      if (root==NULL)
           found = false;
       else if (key < root->key)
           searchElem(key,root->left,found);
       else if (key>root->key)
           searchElem(key,root->right,found);
       else
           found = true;
}


template <class T>
void AVLtree<T>::bracketNotation(AVLnode<T>* root, std::string& str){
     if (root == NULL)
         return;
   
     std::string s = std::to_string(root->key);
     for(char i : s){
         str.push_back(i);
      }
     
     if (!root->left && !root->right)
         return;
   
     // for left subtree
     str.push_back('(');
     bracketNotation(root->left, str);
     str.push_back(')');
   
     // only if right child is present to
     // avoid extra parenthesis
     if (root->right) {
         str.push_back('(');
         bracketNotation(root->right, str);
         str.push_back(')');
     }
 }

template <class T>
void AVLtree<T>::printBaracketNotation(){
     std::string brack;
     int h = height(root);
     bracketNotation(root, brack);
     std::cout << "AVL Bracket view: " << brack<< std::endl;
     std::cout << "Height of Tree: " << h<< std::endl;

 }
 
 
